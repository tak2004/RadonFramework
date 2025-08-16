module;
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include <stdlib.h>
export module rf.core.os:environment;
import rf.core.types;

export namespace rf {

strview getEnvironmentVariable(strview Name, mem Buffer) {
  GetEnvironmentVariableA(reinterpret_cast<LPCSTR>(Name.address),
                          reinterpret_cast<LPSTR>(Buffer.address),
                          Buffer.bytes);
  return strview{Buffer.address, Buffer.bytes};
}

strview getUserVariable(strview Name, mem Buffer) {
  strview result;
  DWORD bytes = 0;
  HKEY hKey;
  LPCTSTR keyPath = TEXT("Environment");
  LSTATUS lOpenStatus =
      RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &hKey);
  if (lOpenStatus == ERROR_SUCCESS) {
    LSTATUS lSetStatus =
        RegQueryValueEx(hKey, reinterpret_cast<LPCSTR>(Name.address), nullptr, nullptr, nullptr, &bytes);
    if (lSetStatus == ERROR_SUCCESS && bytes <= Buffer.bytes) {

      BYTE *keyData = new BYTE[bytes];
      lSetStatus = RegQueryValueEx(hKey, reinterpret_cast<LPCSTR>(Name.address), nullptr, nullptr,
                                   reinterpret_cast<LPBYTE>(Buffer.address), &bytes);
      result.address = Buffer.address;
      result.bytes = bytes;
    }
    RegCloseKey(hKey);
  }
  return result;
}

bool setUserVariable(strview Name, strview Value) {
  bool result = false;
  HKEY hKey;
  LPCTSTR keyPath = TEXT("Environment");
  LSTATUS lOpenStatus =
      RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &hKey);
  if (lOpenStatus == ERROR_SUCCESS) {
    LSTATUS lSetStatus = RegSetKeyValue(hKey, nullptr, reinterpret_cast<LPCSTR>(Name.address), REG_SZ,
                                        Value.address, Value.bytes);
    if (lSetStatus == ERROR_SUCCESS) {
      result = true;
    }
    RegCloseKey(hKey);
  }
  return result;
}

strview getActiveLanguage(mem Buffer) {
  WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
  strview result;
  int writtenBytes =
      GetUserDefaultLocaleName(languageUtf16, LOCALE_USER_DEFAULT);
  if (writtenBytes > 0 && writtenBytes <= Buffer.bytes)
    writtenBytes = wcstombs(reinterpret_cast<char *>(Buffer.address),
                            languageUtf16, Buffer.bytes);
  if (writtenBytes > 0 && writtenBytes <= Buffer.bytes)
    result = strview{Buffer.address, static_cast<size>(writtenBytes)};
  return result;
}

strview getActiveNativeLanguage(mem Buffer) {
  WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
  strview result;
  int writtenBytes =
      GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SNATIVELANGUAGENAME,
                      languageUtf16, LOCALE_NAME_MAX_LENGTH);
  if (writtenBytes > 0 && writtenBytes <= Buffer.bytes)
    writtenBytes = wcstombs(reinterpret_cast<char*>(Buffer.address), languageUtf16, Buffer.bytes);
  if (writtenBytes > 0 && writtenBytes <= Buffer.bytes)
    result = strview{Buffer.address, static_cast<size>(writtenBytes)};
  return result;
}

strview getActiveNativeLanguageLocation(mem Buffer) {
  WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
  strview result;
  int writtenBytes =
      GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SNATIVECOUNTRYNAME,
                      languageUtf16, LOCALE_NAME_MAX_LENGTH);
  if (writtenBytes > 0 && writtenBytes <= Buffer.bytes)
    writtenBytes = wcstombs(reinterpret_cast<char *>(Buffer.address),
                            languageUtf16, Buffer.bytes);
  if (writtenBytes > 0 && writtenBytes <= Buffer.bytes)
    result = strview{Buffer.address, static_cast<size>(writtenBytes)};
  return result;
}
} // namespace rf