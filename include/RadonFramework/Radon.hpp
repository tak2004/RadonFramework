#ifndef RF_RADON_HPP
#define RF_RADON_HPP
#if _MSC_VER > 1000
#pragma once
#endif

//If you change this enum then change the RadonFramework_Init and RadonFramework_Quit function
//in the System.cpp too ! Ah and don't forget to adjust the All value.
namespace RadonFramework
{
    namespace Init{
        enum Type
        {
            All=0x7F,
            Process=1,
            Drawing=2,
            Forms=4,
            Hashing=8,
            IO=0x10,
            Net=0x20,
            SMBios=0x40
        };
    }

    /** This class take care of one time initialized objects and modules.
      * It allows to dispatch, initialize, shutdown and register at a specific
      * point instead of On-Demand.
      */
    class Radon
    {
        public:
            /** @brief This function will be init all manager and services.
              *
              * The function will initialize all services and manager which pass by the Flags parameter.
              * You can also init the systems by your self but this will take more code then use this function.
              */
            Radon(RFTYPE::UInt32 Flags = Init::All);
            /** @brief This function will be clean up all instances and shut down all manager.
              *
              * The function will clean up every manager, remove services and delete used memory.
              * This will only clean up all components which were initialized by RadonFramework_Init function.
              */
            ~Radon();

            void InitSubSystem(RFTYPE::UInt32 Flags);
            void QuitSubSystem(RFTYPE::UInt32 Flags);
            RFTYPE::Bool IsSubSystemInitialized(RFTYPE::UInt32 Flag)const;
        private:
            class PIMPL;
            Memory::AutoPointer<PIMPL> m_PIMPL;
            static RFTYPE::Bool m_IsInitialized;
    };
}

#endif // RF_RADON_HPP
