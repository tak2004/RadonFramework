export module rf.core.system:uuid;
import rf.core.types;
import rf.core.cpu;
import rf.core.os;

export namespace rf {
// UUIDs are usefull if you need identifier which work beyond your process.
struct UUID {
  union {
    u8 raw[16];
    struct {
      u32 a;
      u16 b;
      u16 c;
      u16 d;
      u8 e[6];
    } tuple;
    struct {
      // time order
      u64 timestampA : 48;
      u64 version : 4;
      u64 timestampB : 12;
      // owner
      u32 variant : 2;
      u32 id : 8;
      // sequence
      u32 sequenceA : 22;
      u32 sequenceB;
    } v7;
  };

  operator bool() const;
  bool operator==(UUID const &rhs) const;
  bool operator!=(UUID const &rhs) const;
  bool operator<(UUID const &rhs) const;
  bool operator>(UUID const &rhs) const;
  bool operator<=(UUID const &rhs) const;
  bool operator>=(UUID const &rhs) const;
  static void genV7(UUID &To, timeval SystemTime, u32 Owner, u32 Sequence);
};
UUID NIL = {0};

// ident is a type to hold a 64bit identifier suited for very quick unique ID
// generation. It's properties are:
// - unique
// - sortable by time(throw away old IDs or keep track of the age)
// - distinguish each logical processor
// --- concurrency without synchronization
// --- pinning the thread to a lp enables you to implement ownership detection.
// - sequence counting per logical processor
// - it's a relative timespan
// If you persist the data then add a date-time and the version right next to
// the collection. With the information you're able to transform the IDs to fix
// issues.
struct Ident {
  union {
    u64 raw;
    // v1 is designed as balance between resolution, timespan and current
    // hardware. It's likely that hardware in 11y will work without penalties on
    // 128bit. An overflow of the sequence will be increase the time and reset
    // the sequence.
    struct {
      u64 time : 35;     // 11years timespan with 10ms precision
      u64 sequence : 22; // 4m ids per 10ms
      u64 lpID : 7;      // up to 128 unique lps
    } v1;
    // v2 trade less precision with more IDs per time unit.
    // An overflow of the sequence will be increase the time and reset the
    // sequence.
    struct {
      u64 time : 29;     // 17years timespan with 1s precision
      u64 sequence : 28; // 268m ids per second
      u64 lpID : 7;      // up to 128 unique lps
    } v2;
  };

  operator u64() const;
  bool operator==(Ident const &rhs) const { return this->raw == rhs.raw; };
  bool operator!=(Ident const &rhs) const { return this->raw != rhs.raw; };
};

// Fastest possible implementation with Radon framework API.
bool genUUID7(UUID &To, u8 OwnerID = 0);

// Pass a zeroed mem object to receive the necessary bytes you need to allocate
// and pass. Set ResetInterval to zero will act as a 57bit counter else the time
// will be updated in the specified interval and the counter reset to zero.
size initIdentContext(mem Context, timeval SystemTime, u64 ResetIntervalMS = 0,
                      u8 Version = 1);
// Manually update the timestamp and reset the sequence if it changed.
void updateIdentContext(mem Context, timeval SystemTime,
                        bool AllLogicalProcessor = true, u8 LPIndex = 255);
// Fastest possible implementation with Radon framework API.
Ident genIdent(mem &Context);

UUID::operator bool() const {
  auto result = compare({.address = this, .bytes = sizeof(UUID)},
                        {.address = &NIL, .bytes = sizeof(UUID)});
  return result == 0;
}

bool UUID::operator==(UUID const &rhs) const {
  auto result = compare({.address = this, .bytes = sizeof(UUID)},
                        {.address = &rhs, .bytes = sizeof(UUID)});
  return result == 0;
}

bool UUID::operator!=(UUID const &rhs) const {
  auto result = compare({.address = this, .bytes = sizeof(UUID)},
                        {.address = &rhs, .bytes = sizeof(UUID)});
  return result != 0;
}

bool UUID::operator<(UUID const &rhs) const {
  auto result = compare({.address = this, .bytes = sizeof(UUID)},
                        {.address = &rhs, .bytes = sizeof(UUID)});
  return result < 0;
}

bool UUID::operator>(UUID const &rhs) const {
  auto result = compare({.address = this, .bytes = sizeof(UUID)},
                        {.address = &rhs, .bytes = sizeof(UUID)});
  return result > 0;
}

bool UUID::operator<=(UUID const &rhs) const {
  auto result = compare({.address = this, .bytes = sizeof(UUID)},
                        {.address = &rhs, .bytes = sizeof(UUID)});
  return result <= 0;
}

bool UUID::operator>=(UUID const &rhs) const {
  auto result = compare({.address = this, .bytes = sizeof(UUID)},
                        {.address = &rhs, .bytes = sizeof(UUID)});
  return result >= 0;
}

void UUID::genV7(UUID &To, timeval SystemTime, u32 Owner, u32 Sequence) {
  // Adjust the 4 bit version part in the time and write the whole 64bit.
  u64 bitmask = 0b1111;
  u64 version = 0b1000;
  u64 timestamp = (SystemTime & (~bitmask)) | version;
  // Variant zero can be done quicker by a bit "and" operation with masking
  // variant part zero and everything else one.
  bitmask = ~(3ull << 62);
  u64 ownerseq = ((static_cast<u64>(Owner) << 32) + Sequence) & bitmask;
  // Do two 64 bit assignments.
  reinterpret_cast<u64 *>(&To.v7)[0] = timestamp;
  reinterpret_cast<u64 *>(&To.v7)[1] = ownerseq;
}

bool genUUID7(UUID &To, u8 Owner) {
  static UUID lastUUID = NIL;
  static u64 nextUpdate = 0;
  // Use the cpu timestamp to check if one second is over and get the system
  // time and reset the sequence. This allows a deterministic behaviour because
  // one system call every second else fast path by increasing the sequence.
  auto now = queryPerformanceCounter();
  u64 *last = reinterpret_cast<u64 *>(&lastUUID.v7);
  u64 *next = reinterpret_cast<u64 *>(&To.v7);
  u64 seqMask = 0b1111111111ull << 54;
  if (nextUpdate < now) {
    nextUpdate = now + queryPerformanceFrequency(); // next update in one second
    auto time = getSystemTime();
    u64 bitmask = 0b1111;
    u64 version = 0b1000;
    u64 timestamp = (time & (~bitmask)) | version;
    last[0] = timestamp;
    // Just set variant to one, owner and sequence will be done in the hot path.
    last[1] = 0b01ull << 62;
  }
  // Increment and then write the owner to fix a possible overflow.
  last[1]++;
  lastUUID.v7.id = Owner;

  next[0] = last[0];
  next[1] = last[1];
  return false;
}

struct IdentContext {
  struct LPData {
    u64 nextUpdate;
    Ident currentIdent;
  };
  LPData *lpData;
  u64 resetInterval;
  timeval originTime;
  u8 version;
  u8 lps;
  u8 reserved_8b_allignment[6];
};

size initIdentContext(mem Context, timeval SystemTime, u64 ResetIntervalMS,
                      u8 Version) {
  auto lps = getAvailableLogicalProcessorCount();
  auto bytes = sizeof(IdentContext) + sizeof(IdentContext::LPData) * lps;
  if (Context.bytes >= bytes) {
    auto context = reinterpret_cast<IdentContext *>(Context.address);
    context->version = Version;
    context->originTime = SystemTime;
    context->lps = lps;
    u64 tsc_frequency = ResetIntervalMS;
    if (ResetIntervalMS != 0) {
      u32 tsc_aux; // lp ID
      auto start_tsc = queryLogicalProcessorPerformanceCounter(tsc_aux);
      sleep(100);
      u64 end_tsc = queryLogicalProcessorPerformanceCounter(tsc_aux);
      tsc_frequency = (end_tsc - start_tsc) * ResetIntervalMS / 100;
    }
    context->resetInterval = tsc_frequency;
    context->lpData = reinterpret_cast<IdentContext::LPData *>(context + 1);
    for (auto i = 0; i < lps; ++i) {
      context->lpData[i].currentIdent.v1.lpID = i; // Set the lpID only.
      context->lpData[i].nextUpdate = 0;
    }
  }
  return bytes;
}

void updateIdentContext(mem Context, timeval SystemTime,
                        bool AllLogicalProcessor, u8 LPIndex) {
  auto context = reinterpret_cast<IdentContext *>(Context.address);
  auto relativeSystemTime = SystemTime - context->originTime;
  u64 now = relativeSystemTime;
  if (context->version == 1) {
    now = now / 100000; // 100ns resolution -> 10ms resolution == 100.000
    now = now << 29;
    for (auto i = 0; i < context->lps; ++i) {
      if (AllLogicalProcessor || i == LPIndex) {
        // context->lpData[i].currentIdent.raw =
        // (context->lpData[i].currentIdent.raw & 0xffffffffE0000000) | now;
        context->lpData[i].currentIdent.v1.time = now;
      }
    }
  } else {
    now = now / 10000000; // 100ns resolution -> 1s resolution == 10.000.000
    now = now << 35;
    for (auto i = 0; i < context->lps; ++i) {
      if (AllLogicalProcessor || i == LPIndex) {
        // context->lpData[i].currentIdent.raw =
        // (context->lpData[i].currentIdent.raw & 0xfffffff800000000) | now;
        context->lpData[i].currentIdent.v2.time = now;
      }
    }
  }
}

Ident genIdent(mem &Context) {
  u32 tsc_aux; // lp ID
  auto now = queryLogicalProcessorPerformanceCounter(tsc_aux);
  auto context = reinterpret_cast<IdentContext *>(Context.address);
  IdentContext::LPData &data = context->lpData[tsc_aux];
  if (context->resetInterval != 0 && data.nextUpdate < now) {
    data.nextUpdate = now + context->resetInterval;
    auto systemTime = getSystemTime();
    updateIdentContext(Context, systemTime, false, tsc_aux);
  }
  data.currentIdent.v1.sequence++; // increase sequence by one
  return data.currentIdent;
}

} // namespace rf