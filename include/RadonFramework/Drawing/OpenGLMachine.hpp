#ifndef RF_DRAWING_OPENGLMACHINE_HPP
#define RF_DRAWING_OPENGLMACHINE_HPP
namespace RadonFramework { namespace Drawing {

namespace GLFunctions
{
	enum Type
	{
		ActiveShaderProgram,
		ActiveTexture,
		AttachShader,
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
		BindTextureUnit,
		BindTextures,
		BindTransformFeedback,
		BindVertexArray,
		BindVertexBuffer,
		BindVertexBuffers,
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
		BlitNamedFramebuffer,
		BufferData,
		BufferStorage,
		BufferSubData,
		CheckFramebufferStatus,
		CheckNamedFramebufferStatus,
		ClampColor,
		Clear,
		ClearBufferData,
		ClearBufferSubData,
		ClearBufferfi,
		ClearBufferfv,
		ClearBufferiv,
		ClearBufferuiv,
		ClearColor,
		ClearDepth,
		ClearDepthf,
		ClearNamedBufferData,
		ClearNamedBufferSubData,
		ClearNamedFramebufferfi,
		ClearNamedFramebufferfv,
		ClearNamedFramebufferiv,
		ClearNamedFramebufferuiv,
		ClearStencil,
		ClearTexImage,
		ClearTexSubImage,
		ClientWaitSync,
		ClipControl,
		ColorMask,
		ColorMaski,
		ColorP3ui,
		ColorP3uiv,
		ColorP4ui,
		ColorP4uiv,
		CompileShader,
		CompressedTexImage1D,
		CompressedTexImage2D,
		CompressedTexImage3D,
		CompressedTexSubImage1D,
		CompressedTexSubImage2D,
		CompressedTexSubImage3D,
		CompressedTextureSubImage1D,
		CompressedTextureSubImage2D,
		CompressedTextureSubImage3D,
		CopyBufferSubData,
		CopyImageSubData,
		CopyNamedBufferSubData,
		CopyTexImage1D,
		CopyTexImage2D,
		CopyTexSubImage1D,
		CopyTexSubImage2D,
		CopyTexSubImage3D,
		CopyTextureSubImage1D,
		CopyTextureSubImage2D,
		CopyTextureSubImage3D,
		CreateBuffers,
		CreateFramebuffers,
		CreateProgram,
		CreateProgramPipelines,
		CreateQueries,
		CreateRenderbuffers,
		CreateSamplers,
		CreateShader,
		CreateShaderProgramv,
		CreateTextures,
		CreateTransformFeedbacks,
		CreateVertexArrays,
		CullFace,
		DebugMessageCallback,
		DebugMessageControl,
		DebugMessageInsert,
		DeleteBuffers,
		DeleteFramebuffers,
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
		DisableVertexArrayAttrib,
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
		DrawRangeElements,
		DrawRangeElementsBaseVertex,
		DrawTransformFeedback,
		DrawTransformFeedbackInstanced,
		DrawTransformFeedbackStream,
		DrawTransformFeedbackStreamInstanced,
		Enable,
		EnableVertexArrayAttrib,
		EnableVertexAttribArray,
		Enablei,
		EndConditionalRender,
		EndQuery,
		EndQueryIndexed,
		EndTransformFeedback,
		FenceSync,
		Finish,
		Flush,
		FlushMappedBufferRange,
		FlushMappedNamedBufferRange,
		FramebufferParameteri,
		FramebufferRenderbuffer,
		FramebufferTexture,
		FramebufferTexture1D,
		FramebufferTexture2D,
		FramebufferTexture3D,
		FramebufferTextureLayer,
		FrontFace,
		GenBuffers,
		GenFramebuffers,
		GenProgramPipelines,
		GenQueries,
		GenRenderbuffers,
		GenSamplers,
		GenTextures,
		GenTransformFeedbacks,
		GenVertexArrays,
		GenerateMipmap,
		GenerateTextureMipmap,
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
		GetCompressedTexImage,
		GetCompressedTextureImage,
		GetCompressedTextureSubImage,
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
		GetGraphicsResetStatus,
		GetInteger64i_v,
		GetInteger64v,
		GetIntegeri_v,
		GetIntegerv,
		GetInternalformati64v,
		GetInternalformativ,
		GetMultisamplefv,
		GetNamedBufferParameteri64v,
		GetNamedBufferParameteriv,
		GetNamedBufferPointerv,
		GetNamedBufferSubData,
		GetNamedFramebufferAttachmentParameteriv,
		GetNamedFramebufferParameteriv,
		GetNamedRenderbufferParameteriv,
		GetObjectLabel,
		GetObjectPtrLabel,
		GetPointerv,
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
		GetTexImage,
		GetTexLevelParameterfv,
		GetTexLevelParameteriv,
		GetTexParameterIiv,
		GetTexParameterIuiv,
		GetTexParameterfv,
		GetTexParameteriv,
		GetTextureImage,
		GetTextureLevelParameterfv,
		GetTextureLevelParameteriv,
		GetTextureParameterIiv,
		GetTextureParameterIuiv,
		GetTextureParameterfv,
		GetTextureParameteriv,
		GetTextureSubImage,
		GetTransformFeedbackVarying,
		GetTransformFeedbacki64_v,
		GetTransformFeedbacki_v,
		GetTransformFeedbackiv,
		GetUniformBlockIndex,
		GetUniformIndices,
		GetUniformLocation,
		GetUniformSubroutineuiv,
		GetUniformdv,
		GetUniformfv,
		GetUniformiv,
		GetUniformuiv,
		GetVertexArrayIndexed64iv,
		GetVertexArrayIndexediv,
		GetVertexArrayiv,
		GetVertexAttribIiv,
		GetVertexAttribIuiv,
		GetVertexAttribLdv,
		GetVertexAttribPointerv,
		GetVertexAttribdv,
		GetVertexAttribfv,
		GetVertexAttribiv,
		GetnColorTable,
		GetnCompressedTexImage,
		GetnConvolutionFilter,
		GetnHistogram,
		GetnMapdv,
		GetnMapfv,
		GetnMapiv,
		GetnMinmax,
		GetnPixelMapfv,
		GetnPixelMapuiv,
		GetnPixelMapusv,
		GetnPolygonStipple,
		GetnSeparableFilter,
		GetnTexImage,
		GetnUniformdv,
		GetnUniformfv,
		GetnUniformiv,
		GetnUniformuiv,
		Hint,
		InvalidateBufferData,
		InvalidateBufferSubData,
		InvalidateFramebuffer,
		InvalidateNamedFramebufferData,
		InvalidateNamedFramebufferSubData,
		InvalidateSubFramebuffer,
		InvalidateTexImage,
		InvalidateTexSubImage,
		IsBuffer,
		IsEnabled,
		IsEnabledi,
		IsFramebuffer,
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
		LineWidth,
		LinkProgram,
		LogicOp,
		MapBuffer,
		MapBufferRange,
		MapNamedBuffer,
		MapNamedBufferRange,
		MemoryBarrier,
		MemoryBarrierByRegion,
		MinSampleShading,
		MultiDrawArrays,
		MultiDrawArraysIndirect,
		MultiDrawElements,
		MultiDrawElementsBaseVertex,
		MultiDrawElementsIndirect,
		MultiTexCoordP1ui,
		MultiTexCoordP1uiv,
		MultiTexCoordP2ui,
		MultiTexCoordP2uiv,
		MultiTexCoordP3ui,
		MultiTexCoordP3uiv,
		MultiTexCoordP4ui,
		MultiTexCoordP4uiv,
		NamedBufferData,
		NamedBufferStorage,
		NamedBufferSubData,
		NamedFramebufferDrawBuffer,
		NamedFramebufferDrawBuffers,
		NamedFramebufferParameteri,
		NamedFramebufferReadBuffer,
		NamedFramebufferRenderbuffer,
		NamedFramebufferTexture,
		NamedFramebufferTextureLayer,
		NamedRenderbufferStorage,
		NamedRenderbufferStorageMultisample,
		NormalP3ui,
		NormalP3uiv,
		ObjectLabel,
		ObjectPtrLabel,
		PatchParameterfv,
		PatchParameteri,
		PauseTransformFeedback,
		PixelStoref,
		PixelStorei,
		PointParameterf,
		PointParameterfv,
		PointParameteri,
		PointParameteriv,
		PointSize,
		PolygonMode,
		PolygonOffset,
		PopDebugGroup,
		PrimitiveRestartIndex,
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
		PushDebugGroup,
		QueryCounter,
		ReadBuffer,
		ReadPixels,
		ReadnPixels,
		ReleaseShaderCompiler,
		RenderbufferStorage,
		RenderbufferStorageMultisample,
		ResumeTransformFeedback,
		SampleCoverage,
		SampleMaski,
		SamplerParameterIiv,
		SamplerParameterIuiv,
		SamplerParameterf,
		SamplerParameterfv,
		SamplerParameteri,
		SamplerParameteriv,
		Scissor,
		ScissorArrayv,
		ScissorIndexed,
		ScissorIndexedv,
		SecondaryColorP3ui,
		SecondaryColorP3uiv,
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
		TexCoordP1ui,
		TexCoordP1uiv,
		TexCoordP2ui,
		TexCoordP2uiv,
		TexCoordP3ui,
		TexCoordP3uiv,
		TexCoordP4ui,
		TexCoordP4uiv,
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
		TextureBarrier,
		TextureBuffer,
		TextureBufferRange,
		TextureParameterIiv,
		TextureParameterIuiv,
		TextureParameterf,
		TextureParameterfv,
		TextureParameteri,
		TextureParameteriv,
		TextureStorage1D,
		TextureStorage2D,
		TextureStorage2DMultisample,
		TextureStorage3D,
		TextureStorage3DMultisample,
		TextureSubImage1D,
		TextureSubImage2D,
		TextureSubImage3D,
		TextureView,
		TransformFeedbackBufferBase,
		TransformFeedbackBufferRange,
		TransformFeedbackVaryings,
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
		UnmapNamedBuffer,
		UseProgram,
		UseProgramStages,
		ValidateProgram,
		ValidateProgramPipeline,
		VertexArrayAttribBinding,
		VertexArrayAttribFormat,
		VertexArrayAttribIFormat,
		VertexArrayAttribLFormat,
		VertexArrayBindingDivisor,
		VertexArrayElementBuffer,
		VertexArrayVertexBuffer,
		VertexArrayVertexBuffers,
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
		Viewport,
		ViewportArrayv,
		ViewportIndexedf,
		ViewportIndexedfv,
		WaitSync,
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
		CopyFloat32Reg0,
		CopyFloat64Reg0,
		CopyInt16Reg0,
		CopyInt32Reg0,
		CopyInt64Reg0,
		CopyUInt16Reg0,
		CopyUInt32Reg0,
		CopyUInt64Reg0,
		CopyPtrReg0,
		CopyFloat32Reg1,
		CopyFloat64Reg1,
		CopyInt16Reg1,
		CopyInt32Reg1,
		CopyInt64Reg1,
		CopyUInt16Reg1,
		CopyUInt32Reg1,
		CopyUInt64Reg1,
		CopyPtrReg1,
		CopyFloat32Reg2,
		CopyFloat64Reg2,
		CopyInt16Reg2,
		CopyInt32Reg2,
		CopyInt64Reg2,
		CopyUInt16Reg2,
		CopyUInt32Reg2,
		CopyUInt64Reg2,
		CopyPtrReg2,
		CopyFloat32Reg3,
		CopyFloat64Reg3,
		CopyInt16Reg3,
		CopyInt32Reg3,
		CopyInt64Reg3,
		CopyUInt16Reg3,
		CopyUInt32Reg3,
		CopyUInt64Reg3,
		CopyPtrReg3,
		CopyFloat32Reg4,
		CopyFloat64Reg4,
		CopyInt16Reg4,
		CopyInt32Reg4,
		CopyInt64Reg4,
		CopyUInt16Reg4,
		CopyUInt32Reg4,
		CopyUInt64Reg4,
		CopyPtrReg4,
		CopyFloat32Reg5,
		CopyFloat64Reg5,
		CopyInt16Reg5,
		CopyInt32Reg5,
		CopyInt64Reg5,
		CopyUInt16Reg5,
		CopyUInt32Reg5,
		CopyUInt64Reg5,
		CopyPtrReg5,
		CopyFloat32Reg6,
		CopyFloat64Reg6,
		CopyInt16Reg6,
		CopyInt32Reg6,
		CopyInt64Reg6,
		CopyUInt16Reg6,
		CopyUInt32Reg6,
		CopyUInt64Reg6,
		CopyPtrReg6,
		CopyFloat32Reg7,
		CopyFloat64Reg7,
		CopyInt16Reg7,
		CopyInt32Reg7,
		CopyInt64Reg7,
		CopyUInt16Reg7,
		CopyUInt32Reg7,
		CopyUInt64Reg7,
		CopyPtrReg7,
		CopyFloat32Reg8,
		CopyFloat64Reg8,
		CopyInt16Reg8,
		CopyInt32Reg8,
		CopyInt64Reg8,
		CopyUInt16Reg8,
		CopyUInt32Reg8,
		CopyUInt64Reg8,
		CopyPtrReg8,
		CopyFloat32Reg9,
		CopyFloat64Reg9,
		CopyInt16Reg9,
		CopyInt32Reg9,
		CopyInt64Reg9,
		CopyUInt16Reg9,
		CopyUInt32Reg9,
		CopyUInt64Reg9,
		CopyPtrReg9,
		CopyFloat32Reg10,
		CopyFloat64Reg10,
		CopyInt16Reg10,
		CopyInt32Reg10,
		CopyInt64Reg10,
		CopyUInt16Reg10,
		CopyUInt32Reg10,
		CopyUInt64Reg10,
		CopyPtrReg10,
		CopyFloat32Reg11,
		CopyFloat64Reg11,
		CopyInt16Reg11,
		CopyInt32Reg11,
		CopyInt64Reg11,
		CopyUInt16Reg11,
		CopyUInt32Reg11,
		CopyUInt64Reg11,
		CopyPtrReg11,
		CopyFloat32Reg12,
		CopyFloat64Reg12,
		CopyInt16Reg12,
		CopyInt32Reg12,
		CopyInt64Reg12,
		CopyUInt16Reg12,
		CopyUInt32Reg12,
		CopyUInt64Reg12,
		CopyPtrReg12,
		CopyFloat32Reg13,
		CopyFloat64Reg13,
		CopyInt16Reg13,
		CopyInt32Reg13,
		CopyInt64Reg13,
		CopyUInt16Reg13,
		CopyUInt32Reg13,
		CopyUInt64Reg13,
		CopyPtrReg13,
		CopyFloat32Reg14,
		CopyFloat64Reg14,
		CopyInt16Reg14,
		CopyInt32Reg14,
		CopyInt64Reg14,
		CopyUInt16Reg14,
		CopyUInt32Reg14,
		CopyUInt64Reg14,
		CopyPtrReg14,
		AddrPtrReg0,
		AddrPtrReg1,
		AddrPtrReg2,
		AddrPtrReg3,
		AddrPtrReg4,
		AddrPtrReg5,
		AddrPtrReg6,
		AddrPtrReg7,
		AddrPtrReg8,
		AddrPtrReg9,
		AddrPtrReg10,
		AddrPtrReg11,
		AddrPtrReg12,
		AddrPtrReg13,
		AddrPtrReg14,
		Read4Byte,
		Read8Byte,
		MAX
	};
}

class OpenGLMachine
{
public:
	static void CallFunction(GLFunctions::Type);
	static void CallOpCode(GLOpCode::Type, RF_Type::UInt8*&);
	static const RF_Type::UInt32 RegisterSize=8;
	static const RF_Type::UInt32 RegisterCount=16;
	static RF_Type::UInt8 Registers[RegisterCount*RegisterSize];
	static const RF_Type::UInt8 FunctionParameterCount[GLFunctions::MAX];
};

template<typename T>
struct GetMoveOpCode
{
	static const GLOpCode::Type COMMAND[OpenGLMachine::RegisterCount];
};

template<typename T>
const GLOpCode::Type GetMoveOpCode<T>::COMMAND[] = {
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX
};

template<typename T>
struct GetMoveOpCodeTrait
{
	enum
	{
		SUPPORTED = false
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<RF_Type::Float32>::COMMAND[] = {
	GLOpCode::MoveFloat32Reg0, 
	GLOpCode::MoveFloat32Reg1, 
	GLOpCode::MoveFloat32Reg2, 
	GLOpCode::MoveFloat32Reg3, 
	GLOpCode::MoveFloat32Reg4, 
	GLOpCode::MoveFloat32Reg5, 
	GLOpCode::MoveFloat32Reg6, 
	GLOpCode::MoveFloat32Reg7, 
	GLOpCode::MoveFloat32Reg8, 
	GLOpCode::MoveFloat32Reg9, 
	GLOpCode::MoveFloat32Reg10, 
	GLOpCode::MoveFloat32Reg11, 
	GLOpCode::MoveFloat32Reg12, 
	GLOpCode::MoveFloat32Reg13, 
	GLOpCode::MoveFloat32Reg14
};

template<>
struct GetMoveOpCodeTrait<RF_Type::Float32>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<RF_Type::Float64>::COMMAND[] = {
	GLOpCode::MoveFloat64Reg0, 
	GLOpCode::MoveFloat64Reg1, 
	GLOpCode::MoveFloat64Reg2, 
	GLOpCode::MoveFloat64Reg3, 
	GLOpCode::MoveFloat64Reg4, 
	GLOpCode::MoveFloat64Reg5, 
	GLOpCode::MoveFloat64Reg6, 
	GLOpCode::MoveFloat64Reg7, 
	GLOpCode::MoveFloat64Reg8, 
	GLOpCode::MoveFloat64Reg9, 
	GLOpCode::MoveFloat64Reg10, 
	GLOpCode::MoveFloat64Reg11, 
	GLOpCode::MoveFloat64Reg12, 
	GLOpCode::MoveFloat64Reg13, 
	GLOpCode::MoveFloat64Reg14
};

template<>
struct GetMoveOpCodeTrait<RF_Type::Float64>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<RF_Type::Int16>::COMMAND[] = {
	GLOpCode::MoveInt16Reg0, 
	GLOpCode::MoveInt16Reg1, 
	GLOpCode::MoveInt16Reg2, 
	GLOpCode::MoveInt16Reg3, 
	GLOpCode::MoveInt16Reg4, 
	GLOpCode::MoveInt16Reg5, 
	GLOpCode::MoveInt16Reg6, 
	GLOpCode::MoveInt16Reg7, 
	GLOpCode::MoveInt16Reg8, 
	GLOpCode::MoveInt16Reg9, 
	GLOpCode::MoveInt16Reg10, 
	GLOpCode::MoveInt16Reg11, 
	GLOpCode::MoveInt16Reg12, 
	GLOpCode::MoveInt16Reg13, 
	GLOpCode::MoveInt16Reg14
};

template<>
struct GetMoveOpCodeTrait<RF_Type::Int16>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<RF_Type::Int32>::COMMAND[] = {
	GLOpCode::MoveInt32Reg0, 
	GLOpCode::MoveInt32Reg1, 
	GLOpCode::MoveInt32Reg2, 
	GLOpCode::MoveInt32Reg3, 
	GLOpCode::MoveInt32Reg4, 
	GLOpCode::MoveInt32Reg5, 
	GLOpCode::MoveInt32Reg6, 
	GLOpCode::MoveInt32Reg7, 
	GLOpCode::MoveInt32Reg8, 
	GLOpCode::MoveInt32Reg9, 
	GLOpCode::MoveInt32Reg10, 
	GLOpCode::MoveInt32Reg11, 
	GLOpCode::MoveInt32Reg12, 
	GLOpCode::MoveInt32Reg13, 
	GLOpCode::MoveInt32Reg14
};

template<>
struct GetMoveOpCodeTrait<RF_Type::Int32>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<RF_Type::Int64>::COMMAND[] = {
	GLOpCode::MoveInt64Reg0, 
	GLOpCode::MoveInt64Reg1, 
	GLOpCode::MoveInt64Reg2, 
	GLOpCode::MoveInt64Reg3, 
	GLOpCode::MoveInt64Reg4, 
	GLOpCode::MoveInt64Reg5, 
	GLOpCode::MoveInt64Reg6, 
	GLOpCode::MoveInt64Reg7, 
	GLOpCode::MoveInt64Reg8, 
	GLOpCode::MoveInt64Reg9, 
	GLOpCode::MoveInt64Reg10, 
	GLOpCode::MoveInt64Reg11, 
	GLOpCode::MoveInt64Reg12, 
	GLOpCode::MoveInt64Reg13, 
	GLOpCode::MoveInt64Reg14
};

template<>
struct GetMoveOpCodeTrait<RF_Type::Int64>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<RF_Type::UInt16>::COMMAND[] = {
	GLOpCode::MoveUInt16Reg0, 
	GLOpCode::MoveUInt16Reg1, 
	GLOpCode::MoveUInt16Reg2, 
	GLOpCode::MoveUInt16Reg3, 
	GLOpCode::MoveUInt16Reg4, 
	GLOpCode::MoveUInt16Reg5, 
	GLOpCode::MoveUInt16Reg6, 
	GLOpCode::MoveUInt16Reg7, 
	GLOpCode::MoveUInt16Reg8, 
	GLOpCode::MoveUInt16Reg9, 
	GLOpCode::MoveUInt16Reg10, 
	GLOpCode::MoveUInt16Reg11, 
	GLOpCode::MoveUInt16Reg12, 
	GLOpCode::MoveUInt16Reg13, 
	GLOpCode::MoveUInt16Reg14
};

template<>
struct GetMoveOpCodeTrait<RF_Type::UInt16>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<RF_Type::UInt32>::COMMAND[] = {
	GLOpCode::MoveUInt32Reg0, 
	GLOpCode::MoveUInt32Reg1, 
	GLOpCode::MoveUInt32Reg2, 
	GLOpCode::MoveUInt32Reg3, 
	GLOpCode::MoveUInt32Reg4, 
	GLOpCode::MoveUInt32Reg5, 
	GLOpCode::MoveUInt32Reg6, 
	GLOpCode::MoveUInt32Reg7, 
	GLOpCode::MoveUInt32Reg8, 
	GLOpCode::MoveUInt32Reg9, 
	GLOpCode::MoveUInt32Reg10, 
	GLOpCode::MoveUInt32Reg11, 
	GLOpCode::MoveUInt32Reg12, 
	GLOpCode::MoveUInt32Reg13, 
	GLOpCode::MoveUInt32Reg14
};

template<>
struct GetMoveOpCodeTrait<RF_Type::UInt32>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<RF_Type::UInt64>::COMMAND[] = {
	GLOpCode::MoveUInt64Reg0, 
	GLOpCode::MoveUInt64Reg1, 
	GLOpCode::MoveUInt64Reg2, 
	GLOpCode::MoveUInt64Reg3, 
	GLOpCode::MoveUInt64Reg4, 
	GLOpCode::MoveUInt64Reg5, 
	GLOpCode::MoveUInt64Reg6, 
	GLOpCode::MoveUInt64Reg7, 
	GLOpCode::MoveUInt64Reg8, 
	GLOpCode::MoveUInt64Reg9, 
	GLOpCode::MoveUInt64Reg10, 
	GLOpCode::MoveUInt64Reg11, 
	GLOpCode::MoveUInt64Reg12, 
	GLOpCode::MoveUInt64Reg13, 
	GLOpCode::MoveUInt64Reg14
};

template<>
struct GetMoveOpCodeTrait<RF_Type::UInt64>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetMoveOpCode<void*>::COMMAND[] = {
	GLOpCode::MovePtrReg0, 
	GLOpCode::MovePtrReg1, 
	GLOpCode::MovePtrReg2, 
	GLOpCode::MovePtrReg3, 
	GLOpCode::MovePtrReg4, 
	GLOpCode::MovePtrReg5, 
	GLOpCode::MovePtrReg6, 
	GLOpCode::MovePtrReg7, 
	GLOpCode::MovePtrReg8, 
	GLOpCode::MovePtrReg9, 
	GLOpCode::MovePtrReg10, 
	GLOpCode::MovePtrReg11, 
	GLOpCode::MovePtrReg12, 
	GLOpCode::MovePtrReg13, 
	GLOpCode::MovePtrReg14
};

template<>
struct GetMoveOpCodeTrait<void*>
{
	enum
	{
		SUPPORTED = true
	};
};

template<typename T>
struct GetCopyOpCode
{
	static const GLOpCode::Type COMMAND[OpenGLMachine::RegisterCount];
};

template<typename T>
const GLOpCode::Type GetCopyOpCode<T>::COMMAND[] = {
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX
};

template<typename T>
struct GetCopyOpCodeTrait
{
	enum
	{
		SUPPORTED = false
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<RF_Type::Float32>::COMMAND[] = {
	GLOpCode::CopyFloat32Reg0, 
	GLOpCode::CopyFloat32Reg1, 
	GLOpCode::CopyFloat32Reg2, 
	GLOpCode::CopyFloat32Reg3, 
	GLOpCode::CopyFloat32Reg4, 
	GLOpCode::CopyFloat32Reg5, 
	GLOpCode::CopyFloat32Reg6, 
	GLOpCode::CopyFloat32Reg7, 
	GLOpCode::CopyFloat32Reg8, 
	GLOpCode::CopyFloat32Reg9, 
	GLOpCode::CopyFloat32Reg10, 
	GLOpCode::CopyFloat32Reg11, 
	GLOpCode::CopyFloat32Reg12, 
	GLOpCode::CopyFloat32Reg13, 
	GLOpCode::CopyFloat32Reg14
};

template<>
struct GetCopyOpCodeTrait<RF_Type::Float32>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<RF_Type::Float64>::COMMAND[] = {
	GLOpCode::CopyFloat64Reg0, 
	GLOpCode::CopyFloat64Reg1, 
	GLOpCode::CopyFloat64Reg2, 
	GLOpCode::CopyFloat64Reg3, 
	GLOpCode::CopyFloat64Reg4, 
	GLOpCode::CopyFloat64Reg5, 
	GLOpCode::CopyFloat64Reg6, 
	GLOpCode::CopyFloat64Reg7, 
	GLOpCode::CopyFloat64Reg8, 
	GLOpCode::CopyFloat64Reg9, 
	GLOpCode::CopyFloat64Reg10, 
	GLOpCode::CopyFloat64Reg11, 
	GLOpCode::CopyFloat64Reg12, 
	GLOpCode::CopyFloat64Reg13, 
	GLOpCode::CopyFloat64Reg14
};

template<>
struct GetCopyOpCodeTrait<RF_Type::Float64>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<RF_Type::Int16>::COMMAND[] = {
	GLOpCode::CopyInt16Reg0, 
	GLOpCode::CopyInt16Reg1, 
	GLOpCode::CopyInt16Reg2, 
	GLOpCode::CopyInt16Reg3, 
	GLOpCode::CopyInt16Reg4, 
	GLOpCode::CopyInt16Reg5, 
	GLOpCode::CopyInt16Reg6, 
	GLOpCode::CopyInt16Reg7, 
	GLOpCode::CopyInt16Reg8, 
	GLOpCode::CopyInt16Reg9, 
	GLOpCode::CopyInt16Reg10, 
	GLOpCode::CopyInt16Reg11, 
	GLOpCode::CopyInt16Reg12, 
	GLOpCode::CopyInt16Reg13, 
	GLOpCode::CopyInt16Reg14
};

template<>
struct GetCopyOpCodeTrait<RF_Type::Int16>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<RF_Type::Int32>::COMMAND[] = {
	GLOpCode::CopyInt32Reg0, 
	GLOpCode::CopyInt32Reg1, 
	GLOpCode::CopyInt32Reg2, 
	GLOpCode::CopyInt32Reg3, 
	GLOpCode::CopyInt32Reg4, 
	GLOpCode::CopyInt32Reg5, 
	GLOpCode::CopyInt32Reg6, 
	GLOpCode::CopyInt32Reg7, 
	GLOpCode::CopyInt32Reg8, 
	GLOpCode::CopyInt32Reg9, 
	GLOpCode::CopyInt32Reg10, 
	GLOpCode::CopyInt32Reg11, 
	GLOpCode::CopyInt32Reg12, 
	GLOpCode::CopyInt32Reg13, 
	GLOpCode::CopyInt32Reg14
};

template<>
struct GetCopyOpCodeTrait<RF_Type::Int32>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<RF_Type::Int64>::COMMAND[] = {
	GLOpCode::CopyInt64Reg0, 
	GLOpCode::CopyInt64Reg1, 
	GLOpCode::CopyInt64Reg2, 
	GLOpCode::CopyInt64Reg3, 
	GLOpCode::CopyInt64Reg4, 
	GLOpCode::CopyInt64Reg5, 
	GLOpCode::CopyInt64Reg6, 
	GLOpCode::CopyInt64Reg7, 
	GLOpCode::CopyInt64Reg8, 
	GLOpCode::CopyInt64Reg9, 
	GLOpCode::CopyInt64Reg10, 
	GLOpCode::CopyInt64Reg11, 
	GLOpCode::CopyInt64Reg12, 
	GLOpCode::CopyInt64Reg13, 
	GLOpCode::CopyInt64Reg14
};

template<>
struct GetCopyOpCodeTrait<RF_Type::Int64>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<RF_Type::UInt16>::COMMAND[] = {
	GLOpCode::CopyUInt16Reg0, 
	GLOpCode::CopyUInt16Reg1, 
	GLOpCode::CopyUInt16Reg2, 
	GLOpCode::CopyUInt16Reg3, 
	GLOpCode::CopyUInt16Reg4, 
	GLOpCode::CopyUInt16Reg5, 
	GLOpCode::CopyUInt16Reg6, 
	GLOpCode::CopyUInt16Reg7, 
	GLOpCode::CopyUInt16Reg8, 
	GLOpCode::CopyUInt16Reg9, 
	GLOpCode::CopyUInt16Reg10, 
	GLOpCode::CopyUInt16Reg11, 
	GLOpCode::CopyUInt16Reg12, 
	GLOpCode::CopyUInt16Reg13, 
	GLOpCode::CopyUInt16Reg14
};

template<>
struct GetCopyOpCodeTrait<RF_Type::UInt16>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<RF_Type::UInt32>::COMMAND[] = {
	GLOpCode::CopyUInt32Reg0, 
	GLOpCode::CopyUInt32Reg1, 
	GLOpCode::CopyUInt32Reg2, 
	GLOpCode::CopyUInt32Reg3, 
	GLOpCode::CopyUInt32Reg4, 
	GLOpCode::CopyUInt32Reg5, 
	GLOpCode::CopyUInt32Reg6, 
	GLOpCode::CopyUInt32Reg7, 
	GLOpCode::CopyUInt32Reg8, 
	GLOpCode::CopyUInt32Reg9, 
	GLOpCode::CopyUInt32Reg10, 
	GLOpCode::CopyUInt32Reg11, 
	GLOpCode::CopyUInt32Reg12, 
	GLOpCode::CopyUInt32Reg13, 
	GLOpCode::CopyUInt32Reg14
};

template<>
struct GetCopyOpCodeTrait<RF_Type::UInt32>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<RF_Type::UInt64>::COMMAND[] = {
	GLOpCode::CopyUInt64Reg0, 
	GLOpCode::CopyUInt64Reg1, 
	GLOpCode::CopyUInt64Reg2, 
	GLOpCode::CopyUInt64Reg3, 
	GLOpCode::CopyUInt64Reg4, 
	GLOpCode::CopyUInt64Reg5, 
	GLOpCode::CopyUInt64Reg6, 
	GLOpCode::CopyUInt64Reg7, 
	GLOpCode::CopyUInt64Reg8, 
	GLOpCode::CopyUInt64Reg9, 
	GLOpCode::CopyUInt64Reg10, 
	GLOpCode::CopyUInt64Reg11, 
	GLOpCode::CopyUInt64Reg12, 
	GLOpCode::CopyUInt64Reg13, 
	GLOpCode::CopyUInt64Reg14
};

template<>
struct GetCopyOpCodeTrait<RF_Type::UInt64>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetCopyOpCode<void*>::COMMAND[] = {
	GLOpCode::CopyPtrReg0, 
	GLOpCode::CopyPtrReg1, 
	GLOpCode::CopyPtrReg2, 
	GLOpCode::CopyPtrReg3, 
	GLOpCode::CopyPtrReg4, 
	GLOpCode::CopyPtrReg5, 
	GLOpCode::CopyPtrReg6, 
	GLOpCode::CopyPtrReg7, 
	GLOpCode::CopyPtrReg8, 
	GLOpCode::CopyPtrReg9, 
	GLOpCode::CopyPtrReg10, 
	GLOpCode::CopyPtrReg11, 
	GLOpCode::CopyPtrReg12, 
	GLOpCode::CopyPtrReg13, 
	GLOpCode::CopyPtrReg14
};

template<>
struct GetCopyOpCodeTrait<void*>
{
	enum
	{
		SUPPORTED = true
	};
};

template<typename T>
struct GetAddrOpCode
{
	static const GLOpCode::Type COMMAND[OpenGLMachine::RegisterCount];
};

template<typename T>
const GLOpCode::Type GetAddrOpCode<T>::COMMAND[] = {
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX, 
	GLOpCode::MAX
};

template<typename T>
struct GetAddrOpCodeTrait
{
	enum
	{
		SUPPORTED = false
	};
};

template<>
const GLOpCode::Type GetAddrOpCode<void*>::COMMAND[] = {
	GLOpCode::AddrPtrReg0, 
	GLOpCode::AddrPtrReg1, 
	GLOpCode::AddrPtrReg2, 
	GLOpCode::AddrPtrReg3, 
	GLOpCode::AddrPtrReg4, 
	GLOpCode::AddrPtrReg5, 
	GLOpCode::AddrPtrReg6, 
	GLOpCode::AddrPtrReg7, 
	GLOpCode::AddrPtrReg8, 
	GLOpCode::AddrPtrReg9, 
	GLOpCode::AddrPtrReg10, 
	GLOpCode::AddrPtrReg11, 
	GLOpCode::AddrPtrReg12, 
	GLOpCode::AddrPtrReg13, 
	GLOpCode::AddrPtrReg14
};

template<>
struct GetAddrOpCodeTrait<void*>
{
	enum
	{
		SUPPORTED = true
	};
};

template<RF_Type::Size N>
struct GetReadOpCode
{
	static const GLOpCode::Type COMMAND;
};

template<RF_Type::Size N>
const GLOpCode::Type GetReadOpCode<N>::COMMAND = GLOpCode::MAX;

template<RF_Type::Size N>
struct GetReadOpCodeTrait
{
	enum
	{
		SUPPORTED = false
	};
};

template<>
const GLOpCode::Type GetReadOpCode<4>::COMMAND = GLOpCode::Read4Byte;

template<>
struct GetReadOpCodeTrait<4>
{
	enum
	{
		SUPPORTED = true
	};
};

template<>
const GLOpCode::Type GetReadOpCode<8>::COMMAND = GLOpCode::Read8Byte;

template<>
struct GetReadOpCodeTrait<8>
{
	enum
	{
		SUPPORTED = true
	};
};

}
}
#endif // RF_DRAWING_OPENGLMACHINE_HPP