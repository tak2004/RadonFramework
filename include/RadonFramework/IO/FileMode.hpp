#ifndef RF_IO_FILEMODE_HPP
#define RF_IO_FILEMODE_HPP

namespace RadonFramework::IO::FileMode
{
enum Type
{
  Read,              /// Like "r" of fopen
  TruncateAndWrite,  /// Like "w" of fopen
  Append,            /// Like "a" of fopen
  Open,              /// Like "r+" of fopen
  Create,            /// Like "w+" of fopen
  AppendAndProtect,  /// Like "a+" of fopen
  MAX
};
}

#endif  // RF_IO_FILEMODE_HPP