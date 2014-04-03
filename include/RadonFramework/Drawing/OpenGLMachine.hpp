#ifndef RF_DRAWING_OPENGLMACHINE_HPP
#define RF_DRAWING_OPENGLMACHINE_HPP
#if _MSC_VER > 1000
#pragma once
#endif
namespace RadonFramework
{
	namespace Drawing
	{
		namespace GLFunctions
		{
			enum Type
			{
				Accum,
				ActiveShaderProgram,
				ActiveTexture,
				AlphaFunc,
				AreTexturesResident,
				ArrayElement,
				AttachShader,
				Begin,
				BeginConditionalRender,
				BeginQuery,
				BeginQueryIndexed,
				BeginTransformFeedback,
				BindAttribLocation,
				BindBuffer,
				BindBufferBase,
				BindBufferRange,
				BindBuffersBase,
				BindBuffersRange,
				BindFragDataLocation,
				BindFragDataLocationIndexed,
				BindFramebuffer,
				BindImageTexture,
				BindImageTextures,
				BindProgramPipeline,
				BindRenderbuffer,
				BindSampler,
				BindSamplers,
				BindTexture,
				BindTextures,
				BindTransformFeedback,
				BindVertexArray,
				BindVertexBuffer,
				BindVertexBuffers,
				Bitmap,
				BlendColor,
				BlendEquation,
				BlendEquationSeparate,
				BlendEquationSeparatei,
				BlendEquationi,
				BlendFunc,
				BlendFuncSeparate,
				BlendFuncSeparatei,
				BlendFunci,
				BlitFramebuffer,
				BufferData,
				BufferStorage,
				BufferSubData,
				CallList,
				CallLists,
				CheckFramebufferStatus,
				ClampColor,
				Clear,
				ClearAccum,
				ClearBufferData,
				ClearBufferSubData,
				ClearBufferfi,
				ClearBufferfv,
				ClearBufferiv,
				ClearBufferuiv,
				ClearColor,
				ClearDepth,
				ClearDepthf,
				ClearIndex,
				ClearStencil,
				ClearTexImage,
				ClearTexSubImage,
				ClientActiveTexture,
				ClientWaitSync,
				ClipPlane,
				Color3b,
				Color3bv,
				Color3d,
				Color3dv,
				Color3f,
				Color3fv,
				Color3i,
				Color3iv,
				Color3s,
				Color3sv,
				Color3ub,
				Color3ubv,
				Color3ui,
				Color3uiv,
				Color3us,
				Color3usv,
				Color4b,
				Color4bv,
				Color4d,
				Color4dv,
				Color4f,
				Color4fv,
				Color4i,
				Color4iv,
				Color4s,
				Color4sv,
				Color4ub,
				Color4ubv,
				Color4ui,
				Color4uiv,
				Color4us,
				Color4usv,
				ColorMask,
				ColorMaski,
				ColorMaterial,
				ColorP3ui,
				ColorP3uiv,
				ColorP4ui,
				ColorP4uiv,
				ColorPointer,
				CompileShader,
				CompressedTexImage1D,
				CompressedTexImage2D,
				CompressedTexImage3D,
				CompressedTexSubImage1D,
				CompressedTexSubImage2D,
				CompressedTexSubImage3D,
				CopyBufferSubData,
				CopyImageSubData,
				CopyPixels,
				CopyTexImage1D,
				CopyTexImage2D,
				CopyTexSubImage1D,
				CopyTexSubImage2D,
				CopyTexSubImage3D,
				CreateProgram,
				CreateShader,
				CreateShaderProgramv,
				CullFace,
				DebugMessageCallback,
				DebugMessageControl,
				DebugMessageInsert,
				DeleteBuffers,
				DeleteFramebuffers,
				DeleteLists,
				DeleteProgram,
				DeleteProgramPipelines,
				DeleteQueries,
				DeleteRenderbuffers,
				DeleteSamplers,
				DeleteShader,
				DeleteSync,
				DeleteTextures,
				DeleteTransformFeedbacks,
				DeleteVertexArrays,
				DepthFunc,
				DepthMask,
				DepthRange,
				DepthRangeArrayv,
				DepthRangeIndexed,
				DepthRangef,
				DetachShader,
				Disable,
				DisableClientState,
				DisableVertexAttribArray,
				Disablei,
				DispatchCompute,
				DispatchComputeIndirect,
				DrawArrays,
				DrawArraysIndirect,
				DrawArraysInstanced,
				DrawArraysInstancedBaseInstance,
				DrawBuffer,
				DrawBuffers,
				DrawElements,
				DrawElementsBaseVertex,
				DrawElementsIndirect,
				DrawElementsInstanced,
				DrawElementsInstancedBaseInstance,
				DrawElementsInstancedBaseVertex,
				DrawElementsInstancedBaseVertexBaseInstance,
				DrawPixels,
				DrawRangeElements,
				DrawRangeElementsBaseVertex,
				DrawTransformFeedback,
				DrawTransformFeedbackInstanced,
				DrawTransformFeedbackStream,
				DrawTransformFeedbackStreamInstanced,
				EdgeFlag,
				EdgeFlagPointer,
				EdgeFlagv,
				Enable,
				EnableClientState,
				EnableVertexAttribArray,
				Enablei,
				End,
				EndConditionalRender,
				EndList,
				EndQuery,
				EndQueryIndexed,
				EndTransformFeedback,
				EvalCoord1d,
				EvalCoord1dv,
				EvalCoord1f,
				EvalCoord1fv,
				EvalCoord2d,
				EvalCoord2dv,
				EvalCoord2f,
				EvalCoord2fv,
				EvalMesh1,
				EvalMesh2,
				EvalPoint1,
				EvalPoint2,
				FeedbackBuffer,
				FenceSync,
				Finish,
				Flush,
				FlushMappedBufferRange,
				FogCoordPointer,
				FogCoordd,
				FogCoorddv,
				FogCoordf,
				FogCoordfv,
				Fogf,
				Fogfv,
				Fogi,
				Fogiv,
				FramebufferParameteri,
				FramebufferRenderbuffer,
				FramebufferTexture,
				FramebufferTexture1D,
				FramebufferTexture2D,
				FramebufferTexture3D,
				FramebufferTextureLayer,
				FrontFace,
				Frustum,
				GenBuffers,
				GenFramebuffers,
				GenLists,
				GenProgramPipelines,
				GenQueries,
				GenRenderbuffers,
				GenSamplers,
				GenTextures,
				GenTransformFeedbacks,
				GenVertexArrays,
				GenerateMipmap,
				GetActiveAtomicCounterBufferiv,
				GetActiveAttrib,
				GetActiveSubroutineName,
				GetActiveSubroutineUniformName,
				GetActiveSubroutineUniformiv,
				GetActiveUniform,
				GetActiveUniformBlockName,
				GetActiveUniformBlockiv,
				GetActiveUniformName,
				GetActiveUniformsiv,
				GetAttachedShaders,
				GetAttribLocation,
				GetBooleani_v,
				GetBooleanv,
				GetBufferParameteri64v,
				GetBufferParameteriv,
				GetBufferPointerv,
				GetBufferSubData,
				GetClipPlane,
				GetCompressedTexImage,
				GetDebugMessageLog,
				GetDoublei_v,
				GetDoublev,
				GetError,
				GetFloati_v,
				GetFloatv,
				GetFragDataIndex,
				GetFragDataLocation,
				GetFramebufferAttachmentParameteriv,
				GetFramebufferParameteriv,
				GetInteger64i_v,
				GetInteger64v,
				GetIntegeri_v,
				GetIntegerv,
				GetInternalformati64v,
				GetInternalformativ,
				GetLightfv,
				GetLightiv,
				GetMapdv,
				GetMapfv,
				GetMapiv,
				GetMaterialfv,
				GetMaterialiv,
				GetMultisamplefv,
				GetObjectLabel,
				GetObjectPtrLabel,
				GetPixelMapfv,
				GetPixelMapuiv,
				GetPixelMapusv,
				GetPointerv,
				GetPolygonStipple,
				GetProgramBinary,
				GetProgramInfoLog,
				GetProgramInterfaceiv,
				GetProgramPipelineInfoLog,
				GetProgramPipelineiv,
				GetProgramResourceIndex,
				GetProgramResourceLocation,
				GetProgramResourceLocationIndex,
				GetProgramResourceName,
				GetProgramResourceiv,
				GetProgramStageiv,
				GetProgramiv,
				GetQueryIndexediv,
				GetQueryObjecti64v,
				GetQueryObjectiv,
				GetQueryObjectui64v,
				GetQueryObjectuiv,
				GetQueryiv,
				GetRenderbufferParameteriv,
				GetSamplerParameterIiv,
				GetSamplerParameterIuiv,
				GetSamplerParameterfv,
				GetSamplerParameteriv,
				GetShaderInfoLog,
				GetShaderPrecisionFormat,
				GetShaderSource,
				GetShaderiv,
				GetString,
				GetStringi,
				GetSubroutineIndex,
				GetSubroutineUniformLocation,
				GetSynciv,
				GetTexEnvfv,
				GetTexEnviv,
				GetTexGendv,
				GetTexGenfv,
				GetTexGeniv,
				GetTexImage,
				GetTexLevelParameterfv,
				GetTexLevelParameteriv,
				GetTexParameterIiv,
				GetTexParameterIuiv,
				GetTexParameterfv,
				GetTexParameteriv,
				GetTransformFeedbackVarying,
				GetUniformBlockIndex,
				GetUniformIndices,
				GetUniformLocation,
				GetUniformSubroutineuiv,
				GetUniformdv,
				GetUniformfv,
				GetUniformiv,
				GetUniformuiv,
				GetVertexAttribIiv,
				GetVertexAttribIuiv,
				GetVertexAttribLdv,
				GetVertexAttribPointerv,
				GetVertexAttribdv,
				GetVertexAttribfv,
				GetVertexAttribiv,
				Hint,
				IndexMask,
				IndexPointer,
				Indexd,
				Indexdv,
				Indexf,
				Indexfv,
				Indexi,
				Indexiv,
				Indexs,
				Indexsv,
				Indexub,
				Indexubv,
				InitNames,
				InterleavedArrays,
				InvalidateBufferData,
				InvalidateBufferSubData,
				InvalidateFramebuffer,
				InvalidateSubFramebuffer,
				InvalidateTexImage,
				InvalidateTexSubImage,
				IsBuffer,
				IsEnabled,
				IsEnabledi,
				IsFramebuffer,
				IsList,
				IsProgram,
				IsProgramPipeline,
				IsQuery,
				IsRenderbuffer,
				IsSampler,
				IsShader,
				IsSync,
				IsTexture,
				IsTransformFeedback,
				IsVertexArray,
				LightModelf,
				LightModelfv,
				LightModeli,
				LightModeliv,
				Lightf,
				Lightfv,
				Lighti,
				Lightiv,
				LineStipple,
				LineWidth,
				LinkProgram,
				ListBase,
				LoadIdentity,
				LoadMatrixd,
				LoadMatrixf,
				LoadName,
				LoadTransposeMatrixd,
				LoadTransposeMatrixf,
				LogicOp,
				Map1d,
				Map1f,
				Map2d,
				Map2f,
				MapBuffer,
				MapBufferRange,
				MapGrid1d,
				MapGrid1f,
				MapGrid2d,
				MapGrid2f,
				Materialf,
				Materialfv,
				Materiali,
				Materialiv,
				MatrixMode,
				MemoryBarrier,
				MinSampleShading,
				MultMatrixd,
				MultMatrixf,
				MultTransposeMatrixd,
				MultTransposeMatrixf,
				MultiDrawArrays,
				MultiDrawArraysIndirect,
				MultiDrawElements,
				MultiDrawElementsBaseVertex,
				MultiDrawElementsIndirect,
				MultiTexCoord1d,
				MultiTexCoord1dv,
				MultiTexCoord1f,
				MultiTexCoord1fv,
				MultiTexCoord1i,
				MultiTexCoord1iv,
				MultiTexCoord1s,
				MultiTexCoord1sv,
				MultiTexCoord2d,
				MultiTexCoord2dv,
				MultiTexCoord2f,
				MultiTexCoord2fv,
				MultiTexCoord2i,
				MultiTexCoord2iv,
				MultiTexCoord2s,
				MultiTexCoord2sv,
				MultiTexCoord3d,
				MultiTexCoord3dv,
				MultiTexCoord3f,
				MultiTexCoord3fv,
				MultiTexCoord3i,
				MultiTexCoord3iv,
				MultiTexCoord3s,
				MultiTexCoord3sv,
				MultiTexCoord4d,
				MultiTexCoord4dv,
				MultiTexCoord4f,
				MultiTexCoord4fv,
				MultiTexCoord4i,
				MultiTexCoord4iv,
				MultiTexCoord4s,
				MultiTexCoord4sv,
				MultiTexCoordP1ui,
				MultiTexCoordP1uiv,
				MultiTexCoordP2ui,
				MultiTexCoordP2uiv,
				MultiTexCoordP3ui,
				MultiTexCoordP3uiv,
				MultiTexCoordP4ui,
				MultiTexCoordP4uiv,
				NewList,
				Normal3b,
				Normal3bv,
				Normal3d,
				Normal3dv,
				Normal3f,
				Normal3fv,
				Normal3i,
				Normal3iv,
				Normal3s,
				Normal3sv,
				NormalP3ui,
				NormalP3uiv,
				NormalPointer,
				ObjectLabel,
				ObjectPtrLabel,
				Ortho,
				PassThrough,
				PatchParameterfv,
				PatchParameteri,
				PauseTransformFeedback,
				PixelMapfv,
				PixelMapuiv,
				PixelMapusv,
				PixelStoref,
				PixelStorei,
				PixelTransferf,
				PixelTransferi,
				PixelZoom,
				PointParameterf,
				PointParameterfv,
				PointParameteri,
				PointParameteriv,
				PointSize,
				PolygonMode,
				PolygonOffset,
				PolygonStipple,
				PopAttrib,
				PopClientAttrib,
				PopDebugGroup,
				PopMatrix,
				PopName,
				PrimitiveRestartIndex,
				PrioritizeTextures,
				ProgramBinary,
				ProgramParameteri,
				ProgramUniform1d,
				ProgramUniform1dv,
				ProgramUniform1f,
				ProgramUniform1fv,
				ProgramUniform1i,
				ProgramUniform1iv,
				ProgramUniform1ui,
				ProgramUniform1uiv,
				ProgramUniform2d,
				ProgramUniform2dv,
				ProgramUniform2f,
				ProgramUniform2fv,
				ProgramUniform2i,
				ProgramUniform2iv,
				ProgramUniform2ui,
				ProgramUniform2uiv,
				ProgramUniform3d,
				ProgramUniform3dv,
				ProgramUniform3f,
				ProgramUniform3fv,
				ProgramUniform3i,
				ProgramUniform3iv,
				ProgramUniform3ui,
				ProgramUniform3uiv,
				ProgramUniform4d,
				ProgramUniform4dv,
				ProgramUniform4f,
				ProgramUniform4fv,
				ProgramUniform4i,
				ProgramUniform4iv,
				ProgramUniform4ui,
				ProgramUniform4uiv,
				ProgramUniformMatrix2dv,
				ProgramUniformMatrix2fv,
				ProgramUniformMatrix2x3dv,
				ProgramUniformMatrix2x3fv,
				ProgramUniformMatrix2x4dv,
				ProgramUniformMatrix2x4fv,
				ProgramUniformMatrix3dv,
				ProgramUniformMatrix3fv,
				ProgramUniformMatrix3x2dv,
				ProgramUniformMatrix3x2fv,
				ProgramUniformMatrix3x4dv,
				ProgramUniformMatrix3x4fv,
				ProgramUniformMatrix4dv,
				ProgramUniformMatrix4fv,
				ProgramUniformMatrix4x2dv,
				ProgramUniformMatrix4x2fv,
				ProgramUniformMatrix4x3dv,
				ProgramUniformMatrix4x3fv,
				ProvokingVertex,
				PushAttrib,
				PushClientAttrib,
				PushDebugGroup,
				PushMatrix,
				PushName,
				QueryCounter,
				RasterPos2d,
				RasterPos2dv,
				RasterPos2f,
				RasterPos2fv,
				RasterPos2i,
				RasterPos2iv,
				RasterPos2s,
				RasterPos2sv,
				RasterPos3d,
				RasterPos3dv,
				RasterPos3f,
				RasterPos3fv,
				RasterPos3i,
				RasterPos3iv,
				RasterPos3s,
				RasterPos3sv,
				RasterPos4d,
				RasterPos4dv,
				RasterPos4f,
				RasterPos4fv,
				RasterPos4i,
				RasterPos4iv,
				RasterPos4s,
				RasterPos4sv,
				ReadBuffer,
				ReadPixels,
				Rectd,
				Rectdv,
				Rectf,
				Rectfv,
				Recti,
				Rectiv,
				Rects,
				Rectsv,
				ReleaseShaderCompiler,
				RenderMode,
				RenderbufferStorage,
				RenderbufferStorageMultisample,
				ResumeTransformFeedback,
				Rotated,
				Rotatef,
				SampleCoverage,
				SampleMaski,
				SamplerParameterIiv,
				SamplerParameterIuiv,
				SamplerParameterf,
				SamplerParameterfv,
				SamplerParameteri,
				SamplerParameteriv,
				Scaled,
				Scalef,
				Scissor,
				ScissorArrayv,
				ScissorIndexed,
				ScissorIndexedv,
				SecondaryColor3b,
				SecondaryColor3bv,
				SecondaryColor3d,
				SecondaryColor3dv,
				SecondaryColor3f,
				SecondaryColor3fv,
				SecondaryColor3i,
				SecondaryColor3iv,
				SecondaryColor3s,
				SecondaryColor3sv,
				SecondaryColor3ub,
				SecondaryColor3ubv,
				SecondaryColor3ui,
				SecondaryColor3uiv,
				SecondaryColor3us,
				SecondaryColor3usv,
				SecondaryColorP3ui,
				SecondaryColorP3uiv,
				SecondaryColorPointer,
				SelectBuffer,
				ShadeModel,
				ShaderBinary,
				ShaderSource,
				ShaderStorageBlockBinding,
				StencilFunc,
				StencilFuncSeparate,
				StencilMask,
				StencilMaskSeparate,
				StencilOp,
				StencilOpSeparate,
				TexBuffer,
				TexBufferRange,
				TexCoord1d,
				TexCoord1dv,
				TexCoord1f,
				TexCoord1fv,
				TexCoord1i,
				TexCoord1iv,
				TexCoord1s,
				TexCoord1sv,
				TexCoord2d,
				TexCoord2dv,
				TexCoord2f,
				TexCoord2fv,
				TexCoord2i,
				TexCoord2iv,
				TexCoord2s,
				TexCoord2sv,
				TexCoord3d,
				TexCoord3dv,
				TexCoord3f,
				TexCoord3fv,
				TexCoord3i,
				TexCoord3iv,
				TexCoord3s,
				TexCoord3sv,
				TexCoord4d,
				TexCoord4dv,
				TexCoord4f,
				TexCoord4fv,
				TexCoord4i,
				TexCoord4iv,
				TexCoord4s,
				TexCoord4sv,
				TexCoordP1ui,
				TexCoordP1uiv,
				TexCoordP2ui,
				TexCoordP2uiv,
				TexCoordP3ui,
				TexCoordP3uiv,
				TexCoordP4ui,
				TexCoordP4uiv,
				TexCoordPointer,
				TexEnvf,
				TexEnvfv,
				TexEnvi,
				TexEnviv,
				TexGend,
				TexGendv,
				TexGenf,
				TexGenfv,
				TexGeni,
				TexGeniv,
				TexImage1D,
				TexImage2D,
				TexImage2DMultisample,
				TexImage3D,
				TexImage3DMultisample,
				TexParameterIiv,
				TexParameterIuiv,
				TexParameterf,
				TexParameterfv,
				TexParameteri,
				TexParameteriv,
				TexStorage1D,
				TexStorage2D,
				TexStorage2DMultisample,
				TexStorage3D,
				TexStorage3DMultisample,
				TexSubImage1D,
				TexSubImage2D,
				TexSubImage3D,
				TextureView,
				TransformFeedbackVaryings,
				Translated,
				Translatef,
				Uniform1d,
				Uniform1dv,
				Uniform1f,
				Uniform1fv,
				Uniform1i,
				Uniform1iv,
				Uniform1ui,
				Uniform1uiv,
				Uniform2d,
				Uniform2dv,
				Uniform2f,
				Uniform2fv,
				Uniform2i,
				Uniform2iv,
				Uniform2ui,
				Uniform2uiv,
				Uniform3d,
				Uniform3dv,
				Uniform3f,
				Uniform3fv,
				Uniform3i,
				Uniform3iv,
				Uniform3ui,
				Uniform3uiv,
				Uniform4d,
				Uniform4dv,
				Uniform4f,
				Uniform4fv,
				Uniform4i,
				Uniform4iv,
				Uniform4ui,
				Uniform4uiv,
				UniformBlockBinding,
				UniformMatrix2dv,
				UniformMatrix2fv,
				UniformMatrix2x3dv,
				UniformMatrix2x3fv,
				UniformMatrix2x4dv,
				UniformMatrix2x4fv,
				UniformMatrix3dv,
				UniformMatrix3fv,
				UniformMatrix3x2dv,
				UniformMatrix3x2fv,
				UniformMatrix3x4dv,
				UniformMatrix3x4fv,
				UniformMatrix4dv,
				UniformMatrix4fv,
				UniformMatrix4x2dv,
				UniformMatrix4x2fv,
				UniformMatrix4x3dv,
				UniformMatrix4x3fv,
				UniformSubroutinesuiv,
				UnmapBuffer,
				UseProgram,
				UseProgramStages,
				ValidateProgram,
				ValidateProgramPipeline,
				Vertex2d,
				Vertex2dv,
				Vertex2f,
				Vertex2fv,
				Vertex2i,
				Vertex2iv,
				Vertex2s,
				Vertex2sv,
				Vertex3d,
				Vertex3dv,
				Vertex3f,
				Vertex3fv,
				Vertex3i,
				Vertex3iv,
				Vertex3s,
				Vertex3sv,
				Vertex4d,
				Vertex4dv,
				Vertex4f,
				Vertex4fv,
				Vertex4i,
				Vertex4iv,
				Vertex4s,
				Vertex4sv,
				VertexAttrib1d,
				VertexAttrib1dv,
				VertexAttrib1f,
				VertexAttrib1fv,
				VertexAttrib1s,
				VertexAttrib1sv,
				VertexAttrib2d,
				VertexAttrib2dv,
				VertexAttrib2f,
				VertexAttrib2fv,
				VertexAttrib2s,
				VertexAttrib2sv,
				VertexAttrib3d,
				VertexAttrib3dv,
				VertexAttrib3f,
				VertexAttrib3fv,
				VertexAttrib3s,
				VertexAttrib3sv,
				VertexAttrib4Nbv,
				VertexAttrib4Niv,
				VertexAttrib4Nsv,
				VertexAttrib4Nub,
				VertexAttrib4Nubv,
				VertexAttrib4Nuiv,
				VertexAttrib4Nusv,
				VertexAttrib4bv,
				VertexAttrib4d,
				VertexAttrib4dv,
				VertexAttrib4f,
				VertexAttrib4fv,
				VertexAttrib4iv,
				VertexAttrib4s,
				VertexAttrib4sv,
				VertexAttrib4ubv,
				VertexAttrib4uiv,
				VertexAttrib4usv,
				VertexAttribBinding,
				VertexAttribDivisor,
				VertexAttribFormat,
				VertexAttribI1i,
				VertexAttribI1iv,
				VertexAttribI1ui,
				VertexAttribI1uiv,
				VertexAttribI2i,
				VertexAttribI2iv,
				VertexAttribI2ui,
				VertexAttribI2uiv,
				VertexAttribI3i,
				VertexAttribI3iv,
				VertexAttribI3ui,
				VertexAttribI3uiv,
				VertexAttribI4bv,
				VertexAttribI4i,
				VertexAttribI4iv,
				VertexAttribI4sv,
				VertexAttribI4ubv,
				VertexAttribI4ui,
				VertexAttribI4uiv,
				VertexAttribI4usv,
				VertexAttribIFormat,
				VertexAttribIPointer,
				VertexAttribL1d,
				VertexAttribL1dv,
				VertexAttribL2d,
				VertexAttribL2dv,
				VertexAttribL3d,
				VertexAttribL3dv,
				VertexAttribL4d,
				VertexAttribL4dv,
				VertexAttribLFormat,
				VertexAttribLPointer,
				VertexAttribP1ui,
				VertexAttribP1uiv,
				VertexAttribP2ui,
				VertexAttribP2uiv,
				VertexAttribP3ui,
				VertexAttribP3uiv,
				VertexAttribP4ui,
				VertexAttribP4uiv,
				VertexAttribPointer,
				VertexBindingDivisor,
				VertexP2ui,
				VertexP2uiv,
				VertexP3ui,
				VertexP3uiv,
				VertexP4ui,
				VertexP4uiv,
				VertexPointer,
				Viewport,
				ViewportArrayv,
				ViewportIndexedf,
				ViewportIndexedfv,
				WaitSync,
				WindowPos2d,
				WindowPos2dv,
				WindowPos2f,
				WindowPos2fv,
				WindowPos2i,
				WindowPos2iv,
				WindowPos2s,
				WindowPos2sv,
				WindowPos3d,
				WindowPos3dv,
				WindowPos3f,
				WindowPos3fv,
				WindowPos3i,
				WindowPos3iv,
				WindowPos3s,
				WindowPos3sv,
				MAX
			};
		}

		namespace GLOpCode
		{
			enum Type
			{
				MoveFloat32Reg0=GLFunctions::MAX,
				MoveFloat64Reg0,
				MoveInt16Reg0,
				MoveInt32Reg0,
				MoveInt64Reg0,
				MoveUInt16Reg0,
				MoveUInt32Reg0,
				MoveUInt64Reg0,
				MovePtrReg0,
				MoveFloat32Reg1,
				MoveFloat64Reg1,
				MoveInt16Reg1,
				MoveInt32Reg1,
				MoveInt64Reg1,
				MoveUInt16Reg1,
				MoveUInt32Reg1,
				MoveUInt64Reg1,
				MovePtrReg1,
				MoveFloat32Reg2,
				MoveFloat64Reg2,
				MoveInt16Reg2,
				MoveInt32Reg2,
				MoveInt64Reg2,
				MoveUInt16Reg2,
				MoveUInt32Reg2,
				MoveUInt64Reg2,
				MovePtrReg2,
				MoveFloat32Reg3,
				MoveFloat64Reg3,
				MoveInt16Reg3,
				MoveInt32Reg3,
				MoveInt64Reg3,
				MoveUInt16Reg3,
				MoveUInt32Reg3,
				MoveUInt64Reg3,
				MovePtrReg3,
				MoveFloat32Reg4,
				MoveFloat64Reg4,
				MoveInt16Reg4,
				MoveInt32Reg4,
				MoveInt64Reg4,
				MoveUInt16Reg4,
				MoveUInt32Reg4,
				MoveUInt64Reg4,
				MovePtrReg4,
				MoveFloat32Reg5,
				MoveFloat64Reg5,
				MoveInt16Reg5,
				MoveInt32Reg5,
				MoveInt64Reg5,
				MoveUInt16Reg5,
				MoveUInt32Reg5,
				MoveUInt64Reg5,
				MovePtrReg5,
				MoveFloat32Reg6,
				MoveFloat64Reg6,
				MoveInt16Reg6,
				MoveInt32Reg6,
				MoveInt64Reg6,
				MoveUInt16Reg6,
				MoveUInt32Reg6,
				MoveUInt64Reg6,
				MovePtrReg6,
				MoveFloat32Reg7,
				MoveFloat64Reg7,
				MoveInt16Reg7,
				MoveInt32Reg7,
				MoveInt64Reg7,
				MoveUInt16Reg7,
				MoveUInt32Reg7,
				MoveUInt64Reg7,
				MovePtrReg7,
				MoveFloat32Reg8,
				MoveFloat64Reg8,
				MoveInt16Reg8,
				MoveInt32Reg8,
				MoveInt64Reg8,
				MoveUInt16Reg8,
				MoveUInt32Reg8,
				MoveUInt64Reg8,
				MovePtrReg8,
				MoveFloat32Reg9,
				MoveFloat64Reg9,
				MoveInt16Reg9,
				MoveInt32Reg9,
				MoveInt64Reg9,
				MoveUInt16Reg9,
				MoveUInt32Reg9,
				MoveUInt64Reg9,
				MovePtrReg9,
				MoveFloat32Reg10,
				MoveFloat64Reg10,
				MoveInt16Reg10,
				MoveInt32Reg10,
				MoveInt64Reg10,
				MoveUInt16Reg10,
				MoveUInt32Reg10,
				MoveUInt64Reg10,
				MovePtrReg10,
				MoveFloat32Reg11,
				MoveFloat64Reg11,
				MoveInt16Reg11,
				MoveInt32Reg11,
				MoveInt64Reg11,
				MoveUInt16Reg11,
				MoveUInt32Reg11,
				MoveUInt64Reg11,
				MovePtrReg11,
				MoveFloat32Reg12,
				MoveFloat64Reg12,
				MoveInt16Reg12,
				MoveInt32Reg12,
				MoveInt64Reg12,
				MoveUInt16Reg12,
				MoveUInt32Reg12,
				MoveUInt64Reg12,
				MovePtrReg12,
				MoveFloat32Reg13,
				MoveFloat64Reg13,
				MoveInt16Reg13,
				MoveInt32Reg13,
				MoveInt64Reg13,
				MoveUInt16Reg13,
				MoveUInt32Reg13,
				MoveUInt64Reg13,
				MovePtrReg13,
				MoveFloat32Reg14,
				MoveFloat64Reg14,
				MoveInt16Reg14,
				MoveInt32Reg14,
				MoveInt64Reg14,
				MoveUInt16Reg14,
				MoveUInt32Reg14,
				MoveUInt64Reg14,
				MovePtrReg14,
				MAX
			};
		}

		class OpenGLMachine
		{
			public:
				static void CallFunction(GLFunctions::Type);
				static void CallOpCode(GLOpCode::Type, RFTYPE::UInt8*&);
				static const RFTYPE::UInt32 RegisterSize=8;
				static const RFTYPE::UInt32 RegisterCount=15;
				static RFTYPE::UInt8 Registers[RegisterCount*RegisterSize];
				static RFTYPE::UInt8 FunctionParameterCount[GLFunctions::MAX];
		};
	}
}
#endif // RF_DRAWING_OPENGLMACHINE_HPP