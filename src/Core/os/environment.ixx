export module rf.core.os:environment;
import rf.core.types;

export namespace rf {
/// Return the specified system environment variable e.g. %TEMP% on Windows.
strview getEnvironmentVariable(strview Name, mem Buffer);
/// This function requests the specified environment variable and return true
/// if the Result parameter was written else false.
strview getUserVariable(strview Name, mem Buffer);
/// This function writes the specified value to the variable name and return true
/// else nothing happen and false will be returned.
bool setUserVariable(strview Name, strview Value);
/// Return the current active user language definition e.g. de_DE.
strview getActiveLanguage(mem Buffer);
/// Return the current active user language name in the native language e.g.
/// Deutsch.
strview getActiveNativeLanguage(mem Buffer);
/// Return the current active user language location in native language e.g.
/// Deutschland.
strview getActiveNativeLanguageLocation(mem Buffer);
}