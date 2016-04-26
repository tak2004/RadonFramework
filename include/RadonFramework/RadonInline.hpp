/*
*
* THIS FILE IS GENERATED FROM build/code_templates/RadonInline.hxx !!!
*
*/
#include <RadonFramework/Defines.hpp>
#include <RadonFramework/precompiled.hpp>

// Each compiler can implement it on it's own way.
#include <stdarg.h>
// Basic types
#include <stdint.h>

#ifndef RF_NO_COLLECTIONS

#include <RadonFramework/Collections/Algorithm/BinarySearch.hpp>
#include <RadonFramework/Collections/Algorithm/Exists.hpp>
#include <RadonFramework/Collections/Algorithm/FindAll.hpp>
#include <RadonFramework/Collections/Algorithm/ForEach.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/ArrayEnumerator.hpp>
#include <RadonFramework/Collections/ArrayEnumeratorType.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Collections/AVLTree.hpp>
#include <RadonFramework/Collections/BitArray.hpp>
#include <RadonFramework/Collections/BitSet.hpp>
#include <RadonFramework/Collections/DataTree.hpp>
#include <RadonFramework/Collections/Enumerator.hpp>
#include <RadonFramework/Collections/HashList.hpp>
#include <RadonFramework/Collections/HashMap.hpp>
#include <RadonFramework/Collections/IEnumerable.hpp>
#include <RadonFramework/Collections/IEnumerator.hpp>
#include <RadonFramework/Collections/LinkedEnumerator.hpp>
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Collections/Pair.hpp>
#include <RadonFramework/Collections/Queue.hpp>
#include <RadonFramework/Collections/Stack.hpp>
#include <RadonFramework/Collections/Tree.hpp>
#endif

#ifndef RF_NO_CORE

#include <RadonFramework/Core/Common/DataManagment.hpp>
#include <RadonFramework/Core/Common/StringCache.hpp>
#include <RadonFramework/Core/Common/Version.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Core/Pattern/Signal.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Core/Pattern/Typelist.hpp>
#include <RadonFramework/Core/Policies/CMemoryOperation.hpp>
#include <RadonFramework/Core/Policies/Comparsion.hpp>
#include <RadonFramework/Core/Policies/CPPAllocator.hpp>
#include <RadonFramework/Core/Policies/LazyResize.hpp>
#include <RadonFramework/Core/Policies/MallocAllocator.hpp>
#include <RadonFramework/Core/Policies/ObjectLogic.hpp>
#include <RadonFramework/Core/Policies/StringProcessor/BruteForce.hpp>
#include <RadonFramework/Core/Policies/StringProcessor/Horspool.hpp>
#include <RadonFramework/Core/Policies/StringProcessor/KnuthMorrisPratt.hpp>
#include <RadonFramework/Core/Policies/StringProcessor/ShiftAnd.hpp>
#include <RadonFramework/Core/Policies/StringProcessor/SkipSearch.hpp>
#include <RadonFramework/Core/Policies/StringProcessor/Sunday.hpp>
#include <RadonFramework/Core/Traits/AllocatorTraits.hpp>
#include <RadonFramework/Core/Types/AtomicInt32.hpp>
#include <RadonFramework/Core/Types/AtomicInt64.hpp>
#include <RadonFramework/Core/Types/AtomicPointer.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Char.hpp>
#include <RadonFramework/Core/Types/Convert.hpp>
#include <RadonFramework/Core/Types/DynamicString.hpp>
#include <RadonFramework/Core/Types/FixString.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Float64.hpp>
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/MemoryRange.hpp>
#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/StringUtils/Base16.hpp>
#include <RadonFramework/Core/Types/StringUtils/Base2.hpp>
#include <RadonFramework/Core/Types/StringUtils/Base64.hpp>
#include <RadonFramework/Core/Types/StringUtils/Base85.hpp>
#include <RadonFramework/Core/Types/StringUtils/JavaScript.hpp>
#include <RadonFramework/Core/Types/StringUtils/StringProcessor.hpp>
#include <RadonFramework/Core/Types/StringUtils/URL.hpp>
#include <RadonFramework/Core/Types/TypeCode.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/Utils/StringBuilder.hpp>
#include <RadonFramework/Core/Types/Utils/StringOperators.hpp>
#include <RadonFramework/Core/Types/Vec.hpp>
#include <RadonFramework/Core/Types/Vec128Float.hpp>
#include <RadonFramework/Core/Types/Vec128Int.hpp>
#include <RadonFramework/Core/Types/Vec128UInt.hpp>
#include <RadonFramework/Core/Types/Vec64Int.hpp>
#include <RadonFramework/Core/Types/Vec64UInt.hpp>
#endif

#ifndef RF_NO_DIAGNOSTICS

#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <RadonFramework/Diagnostics/Debugging/Error.hpp>
#include <RadonFramework/Diagnostics/Debugging/FrameworkDiagnostics.hpp>
#include <RadonFramework/Diagnostics/Debugging/ScopeLogMessage.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/BriefProgressCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/DebugCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/JUnitOutput.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestResultCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ProcessInformation.hpp>
#endif

#ifndef RF_NO_DRAWING

#include <RadonFramework/Drawing/Camera.hpp>
#include <RadonFramework/Drawing/Canvas3D.hpp>
#include <RadonFramework/Drawing/Canvas3DService.hpp>
#include <RadonFramework/Drawing/Canvas3DServiceConfig.hpp>
#include <RadonFramework/Drawing/Canvas3DServiceLocator.hpp>
#include <RadonFramework/Drawing/Color.hpp>
#include <RadonFramework/Drawing/FontService.hpp>
#include <RadonFramework/Drawing/FontServiceLocator.hpp>
#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Drawing/Forms/DisplayInformation.hpp>
#include <RadonFramework/Drawing/Forms/Form.hpp>
#include <RadonFramework/Drawing/Forms/IApplication.hpp>
#include <RadonFramework/Drawing/Forms/IWindow.hpp>
#include <RadonFramework/Drawing/Forms/Label.hpp>
#include <RadonFramework/Drawing/Forms/Resolution.hpp>
#include <RadonFramework/Drawing/Forms/Screen.hpp>
#include <RadonFramework/Drawing/Forms/WindowService.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/Drawing/GraphicDriverInformation.hpp>
#include <RadonFramework/Drawing/ICanvas3D.hpp>
#include <RadonFramework/Drawing/MeshGenerator2D.hpp>
#include <RadonFramework/Drawing/OpenGLCapabilities.hpp>
#include <RadonFramework/Drawing/OpenGLCapabilitiesType.hpp>
#include <RadonFramework/Drawing/PixelFormat.hpp>
#include <RadonFramework/Drawing/PopupMenu.hpp>
#include <RadonFramework/Drawing/SystemTray.hpp>
#include <RadonFramework/Drawing/TrayIcon.hpp>
#endif

#ifndef RF_NO_IO

#include <RadonFramework/IO/AccessMode.hpp>
#include <RadonFramework/IO/ConsoleColor.hpp>
#include <RadonFramework/IO/Decoder.hpp>
#include <RadonFramework/IO/Decoders/ImageDecoder.hpp>
#include <RadonFramework/IO/Decoders/Interface.hpp>
#include <RadonFramework/IO/DecoderService.hpp>
#include <RadonFramework/IO/DecoderServiceLocator.hpp>
#include <RadonFramework/IO/Directory.hpp>
#include <RadonFramework/IO/Encoder.hpp>
#include <RadonFramework/IO/Encoders/ImageEncoder.hpp>
#include <RadonFramework/IO/Encoders/Interface.hpp>
#include <RadonFramework/IO/EncoderService.hpp>
#include <RadonFramework/IO/EncoderServiceLocator.hpp>
#include <RadonFramework/IO/File.hpp>
#include <RadonFramework/IO/FileMode.hpp>
#include <RadonFramework/IO/FileProtocolService.hpp>
#include <RadonFramework/IO/FileStatus.hpp>
#include <RadonFramework/IO/FileStream.hpp>
#include <RadonFramework/IO/FileWatcher.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/IO/LogConfig.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/IO/LogDebuggerOutput.hpp>
#include <RadonFramework/IO/MemoryCollectionStream.hpp>
#include <RadonFramework/IO/MemoryProtocolService.hpp>
#include <RadonFramework/IO/MemoryStream.hpp>
#include <RadonFramework/IO/MouseEvent.hpp>
#include <RadonFramework/IO/OptionRule.hpp>
#include <RadonFramework/IO/OptionValue.hpp>
#include <RadonFramework/IO/Parameter.hpp>
#include <RadonFramework/IO/ProtocolService.hpp>
#include <RadonFramework/IO/ProtocolServiceLocator.hpp>
#include <RadonFramework/IO/Resource.hpp>
#include <RadonFramework/IO/SeekOrigin.hpp>
#include <RadonFramework/IO/Settings.hpp>
#include <RadonFramework/IO/StandardRuleChecker.hpp>
#include <RadonFramework/IO/Stream.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/IO/UriComponents.hpp>
#include <RadonFramework/IO/UriFormat.hpp>
#include <RadonFramework/IO/UriHostNameType.hpp>
#include <RadonFramework/IO/UriKind.hpp>
#include <RadonFramework/IO/UriPartial.hpp>
#include <RadonFramework/IO/VirtualKey.hpp>
#include <RadonFramework/IO/VirtualMouseButton.hpp>
#endif

#ifndef RF_NO_MATH

#include <RadonFramework/Math/Float32.hpp>
#include <RadonFramework/Math/Float64.hpp>
#include <RadonFramework/Math/Geometry/CubicBezier.hpp>
#include <RadonFramework/Math/Geometry/Line.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/ProjectionMatrix.hpp>
#include <RadonFramework/Math/Geometry/Quaternion.hpp>
#include <RadonFramework/Math/Geometry/QuatF32.hpp>
#include <RadonFramework/Math/Geometry/QuatF64.hpp>
#include <RadonFramework/Math/Geometry/Rectangle.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/Math/Geometry/Vector.hpp>
#include <RadonFramework/Math/Hash/Hash.hpp>
#include <RadonFramework/Math/Hash/HashfunctionService.hpp>
#include <RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp>
#include <RadonFramework/Math/Hash/IHashfunction.hpp>
#include <RadonFramework/Math/Integer.hpp>
#include <RadonFramework/Math/Math.hpp>
#include <RadonFramework/Math/Random.hpp>
#endif

#ifndef RF_NO_MEMORY

#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/DoubleSideStackAllocator.hpp>
#include <RadonFramework/Memory/FixedLengthAllocator.hpp>
#include <RadonFramework/Memory/LinearAllocator.hpp>
#include <RadonFramework/Memory/ManagedInstanceStackAllocator.hpp>
#include <RadonFramework/Memory/MemoryInfo.hpp>
#include <RadonFramework/Memory/MemoryOperation.hpp>
#include <RadonFramework/Memory/PointerID.hpp>
#include <RadonFramework/Memory/ReadBuffer.hpp>
#include <RadonFramework/Memory/StackAllocator.hpp>
#endif

#ifndef RF_NO_NET

#include <RadonFramework/Net/AddressFamily.hpp>
#include <RadonFramework/Net/EndPoint.hpp>
#include <RadonFramework/Net/Error.hpp>
#include <RadonFramework/Net/FixedLengthString.hpp>
#include <RadonFramework/Net/IPAddress.hpp>
#include <RadonFramework/Net/IPHostEntry.hpp>
#include <RadonFramework/Net/mDNS/Message.hpp>
#include <RadonFramework/Net/mDNS/MessageReader.hpp>
#include <RadonFramework/Net/mDNS/MessageWriter.hpp>
#include <RadonFramework/Net/mDNS/NetworkService.hpp>
#include <RadonFramework/Net/mDNS/ServiceDiscovery.hpp>
#include <RadonFramework/Net/mDNS/ServiceDiscoveryView.hpp>
#include <RadonFramework/Net/mDNS/ServiceResponder.hpp>
#include <RadonFramework/Net/MulticastRequest.hpp>
#include <RadonFramework/Net/NetworkAdapter.hpp>
#include <RadonFramework/Net/NetworkStream.hpp>
#include <RadonFramework/Net/PacketStream.hpp>
#include <RadonFramework/Net/PacketWithHeader.hpp>
#include <RadonFramework/Net/SelectMode.hpp>
#include <RadonFramework/Net/Server.hpp>
#include <RadonFramework/Net/ServerConfig.hpp>
#include <RadonFramework/Net/Service.hpp>
#include <RadonFramework/Net/SessionServer.hpp>
#include <RadonFramework/Net/Socket.hpp>
#include <RadonFramework/Net/SocketError.hpp>
#include <RadonFramework/Net/SocketOptionLevel.hpp>
#include <RadonFramework/Net/SocketOptionName.hpp>
#include <RadonFramework/Net/SocketShutdown.hpp>
#include <RadonFramework/Net/SocketType.hpp>
#endif

#ifndef RF_NO_REFLECTION

#include <RadonFramework/Reflection/ParameterStack.hpp>
#include <RadonFramework/Reflection/Reflectable.hpp>
#include <RadonFramework/Reflection/ReflectionClass.hpp>
#include <RadonFramework/Reflection/ReflectionManager.hpp>
#include <RadonFramework/Reflection/ReflectionMethode.hpp>
#include <RadonFramework/Reflection/ReflectionProperty.hpp>
#include <RadonFramework/Reflection/ReflectionTypes.hpp>
#endif

#ifndef RF_NO_THREADING

#include <RadonFramework/Threading/IRunnable.hpp>
#include <RadonFramework/Threading/ISynchronize.hpp>
#include <RadonFramework/Threading/IWaitHandle.hpp>
#include <RadonFramework/Threading/Policies/NoSynchronization.hpp>
#include <RadonFramework/Threading/RegisteredWaitHandle.hpp>
#include <RadonFramework/Threading/Scopelock.hpp>
#include <RadonFramework/Threading/TaskStrategy.hpp>
#include <RadonFramework/Threading/Thread.hpp>
#include <RadonFramework/Threading/ThreadError.hpp>
#include <RadonFramework/Threading/ThreadPool.hpp>
#include <RadonFramework/Threading/ThreadPriority.hpp>
#include <RadonFramework/Threading/Timer.hpp>
#endif

#ifndef RF_NO_TIME

#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/Framecounter.hpp>
#include <RadonFramework/Time/ScopeTimer.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#endif

#ifndef RF_NO_TEXT

#include <RadonFramework/Text/Regex.hpp>
#include <RadonFramework/Text/UnicodeRangeInfo.hpp>
#endif

#ifndef RF_NO_UTIL

#include <RadonFramework/Util/UUID.hpp>
#endif
