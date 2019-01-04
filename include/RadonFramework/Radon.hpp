#ifndef RF_RADON_HPP
#define RF_RADON_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/RadonInline.hpp>

// If you change this enum then do it in RadonFramework_Init and
// RadonFramework_Quit function too and don't forget to adjust the Type::All
// value.
namespace RadonFramework::Init
{
enum Type
{
  All = 0x7FF,
  Core = 1,
  Hashing = 8,
  IO = 0x10,
  Net = 0x20,
  Diagnostics = 0x40,
  Time = 0x80,
  Memory = 0x100,
  Process = 0x200,
  Threading = 0x400,
  Security = 0x800
};
}

namespace RadonFramework
{
/** This class take care of one time initialized objects and modules.
 * It allows to dispatch, initialize, shutdown and register at a specific
 * point instead of On-Demand.
 */
class Radon
{
public:
  /** @brief This function will be init all manager and services.
   *
   * The function will initialize all services and manager which pass by the
   * Flags parameter. You can also init the systems by your self but this will
   * take more code then use this function.
   */
  Radon(RF_Type::UInt32 Flags = Init::All);
  /** @brief This function will be clean up all instances and shut down all
   * manager.
   *
   * The function will clean up every manager, remove services and delete used
   * memory. This will only clean up all components which were initialized by
   * RadonFramework_Init function.
   */
  ~Radon();

  void InitSubSystem(RF_Type::UInt32 Flags);
  void QuitSubSystem(RF_Type::UInt32 Flags);
  RF_Type::Bool IsSubSystemInitialized(RF_Type::UInt32 Flag) const;

private:
  class PIMPL;
  Memory::AutoPointer<PIMPL> m_PIMPL;
  static RF_Type::Bool m_IsInitialized;
};

}  // namespace RadonFramework

#endif  // RF_RADON_HPP
