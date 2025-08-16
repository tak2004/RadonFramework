export module rf.core.io:file;
import rf.core.types;
import :directory;

export namespace rf{
class File {
public:
  /// <summary>
  /// This factory function takes a native path, clean it up, convert it in an abstract
  /// representation and creates a File object from it.
  /// </summary>
  /// <param name="Path">The native path used by the factory function.</param>
  /// <param name="Target">The target to which the function writes on success.</param>
  /// <returns>True if the function wrote to the Target parameter else false.</returns>
  static bool CreateFromNativePath(strview Path, File &Target);
  /// <summary>
  /// This factory function takes a abstract path and creates a File object from it.
  /// </summary>
  /// <param name="Path">The abstract path used by the factory function.</param>
  /// <param name="Target">The target to which the function writes on success.</param>
  /// <returns>True if the function wrote to the Target parameter else false.</returns>
  static bool CreateFromAbstractPath(strview Path, File &Target);
  /// Create a default Directory object and set the filename to "unset".
  File();
  File(Directory Dir, strview Filename);
  bool create(const bool Recursive = true) const;
  bool preallocate(const size Bytes) const;
  bool erase() const;
  bool copyTo(const Directory &Destination) const;
  bool copyRelativeTo(const Directory &Base, const Directory &Destination) const;
  bool renameTo(strview NewName);
  bool hardLinkTo(const File &Destination) const;
  /// You can use CanCreateSoftLink method to verify if you're allowed to create a softlink.
  bool softLinkTo(const File &Destination) const;

  bool write(const void *Data, const size Bytes) const;
  size read(void *Buffer, const size MaximumBytes) const;

  bool exists() const;
  bool isReadable() const;
  bool isWritable() const;
  bool isHidden() const;
  bool isHardLink() const;
  bool isSoftLink() const;
  /// On Windows you need a admin role to create softlinks. 
  bool canCreateSoftLink() const;
  strview name() const;
  strview nameWithoutExtension() const;
  strview extension() const;
  u64 lastModified() const;
  u64 createdAt() const;
  u64 lastAccess() const;
  size bytes() const;
  str toNativePath() const;
  const Directory &directory() const;
  size hardLinkCount() const;
private:
  Directory dir;
  str filename;
};
}