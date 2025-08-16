export module rf.core.io:directory;
import rf.core.types;

export namespace rf {
class Directory {
public:
  /// <summary>
  /// This factory function takes a native path, clean it up, convert it in an abstract
  /// representation and creates a Directory object from it.
  /// </summary>
  /// <param name="Path">The native path used by the factory function.</param>
  /// <returns>A Directory object.</returns>
  static Directory CreateFromNativePath(strview Path);
  /// <summary>
  /// This factory function takes a abstract path, clean it up and creates a Directory object from
  /// it.
  /// </summary>
  /// <param name="Path">The abstract path used by the factory function.</param>
  /// <returns>A Directory object.</returns>
  static Directory CreateFromAbstractPath(strview Path);
  /// Return the directory from where the application was started.
  static Directory Working();
  /// Return the the user's home directory.
  static Directory Home();
  /// Return the directory where the running application is located.
  static Directory Application();
  /// Return the data directory for 'current user' which belongs to the running application.
  static Directory UserApplicationData();
  /// Return the data directory for 'all user' which belongs to the running application.
  static Directory ApplicationData();
  /// Return the temporary directory of the system.
  static Directory Temporary();

  /// The default directory is the root of the filesystem('/').
  Directory();
  bool create(const bool Recursive = true) const;
  bool erase() const;
  bool renameTo(strview NewName);
  Directory operator/(strview Subdir) const;  
  bool softLinkTo(const Directory &Destination) const;

  bool exists() const;
  bool isReadable() const;
  bool isWritable() const;
  strview name() const;
  strview location() const;  
  // If this directory is a subdir of Other then return the relative part else a empty StringView.
  strview relativeTo(const Directory &Other) const;
  bool isHidden() const;
  bool hasParent() const;
  u64 lastModified() const;
  u64 createdAt() const;
  u64 lastAccess() const;
  str toNativePath() const;
  arr<str> files() const;
  arr<str> directories() const;
  // Return the parent or the root of the filesystem.
  Directory parent() const;
private:
  static str CleanupInput(strview Input);
  str path;
};
}