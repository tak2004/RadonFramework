#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Drawing/OpenGLMachine.hpp>
#include <GL/glew.h>

using namespace RadonFramework::Drawing;
using namespace RadonFramework::Core::Types;

UInt8 OpenGLMachine::Registers[OpenGLMachine::RegisterCount*OpenGLMachine::RegisterSize];
UInt8 OpenGLMachine::FunctionParameterCount[GLFunctions::MAX]={
	2, 2, 1, 2, 3, 1, 2, 1, 2, 2, 3, 1, 3, 2, 3, 5, 4, 6, 3, 4, 2, 7, 3, 1, 2,
	2, 3, 2, 3, 2, 1, 4, 5, 7, 4, 1, 2, 3, 2, 2, 4, 5, 3, 10, 4, 4, 4, 1, 3, 1,
	2, 1, 4, 5, 7, 4, 3, 3, 3, 4, 1, 1, 1, 1, 5, 11, 1, 3, 2, 3, 1, 3, 1, 3, 1,
	3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4,
	1, 4, 5, 2, 2, 2, 2, 2, 4, 1, 7, 8, 9, 7, 9, 11, 5, 15, 5, 7, 8, 6, 8, 9, 0,
	1, 3, 1, 2, 6, 6, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 3, 3, 2,
	2, 1, 1, 1, 2, 3, 1, 3, 2, 4, 5, 1, 2, 4, 5, 3, 5, 6, 6, 7, 5, 6, 7, 2, 3,
	3, 4, 1, 2, 1, 1, 1, 1, 2, 0, 0, 0, 1, 2, 0, 1, 1, 1, 1, 2, 1, 2, 1, 3, 5,
	1, 2, 3, 2, 0, 0, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 4, 5, 5, 6, 5, 1, 6,
	2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 4, 7, 6, 6, 5, 7, 5, 4, 5, 5, 4, 2, 3, 2,
	3, 3, 3, 4, 2, 3, 8, 3, 2, 0, 3, 2, 2, 2, 4, 3, 3, 2, 3, 2, 5, 5, 3, 3, 3,
	3, 3, 3, 3, 3, 5, 4, 2, 2, 2, 2, 1, 5, 4, 4, 4, 3, 3, 3, 3, 6, 8, 4, 3, 4,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 3, 1, 2, 3, 3, 5, 3, 3, 3, 3, 3, 5,
	4, 4, 3, 3, 3, 3, 7, 2, 4, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 3,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 1, 3, 3, 7, 2, 8, 1, 1, 2, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 2, 1, 1, 1, 0, 1, 1, 1, 1,
	1, 1, 6, 6, 10, 10, 2, 4, 3, 3, 6, 6, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 4, 4,
	5, 6, 5, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 3, 2, 3, 2, 3, 2, 4, 2, 4, 2, 4, 2,
	4, 2, 5, 2, 5, 2, 5, 2, 5, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1, 3, 1, 3, 1,
	3, 1, 3, 1, 2, 2, 3, 4, 3, 6, 1, 2, 2, 0, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 1, 2, 2, 1, 0, 0, 0, 0, 0, 1, 3, 4, 3, 3, 4, 3, 4, 3, 4, 3, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 5, 4, 5, 4, 5, 4, 5, 4, 6, 4, 6, 4, 6, 4, 6, 4, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 4, 0, 1, 2, 2, 1, 2, 1,
	2, 1, 2, 1, 3, 1, 3, 1, 3, 1, 3, 1, 4, 1, 4, 1, 4, 1, 4, 1, 1, 7, 4, 2, 4,
	2, 4, 2, 4, 2, 0, 1, 4, 5, 0, 4, 4, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 5,
	2, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 2, 2, 4, 2, 1, 5, 4, 3,
	3, 4, 1, 2, 3, 4, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3,
	1, 3, 1, 3, 1, 3, 1, 4, 1, 4, 1, 4, 1, 4, 1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 8, 9, 6, 10, 7, 3, 3, 3, 3, 3, 3, 4, 5, 6, 6, 7,
	7, 9, 11, 8, 4, 3, 3, 2, 3, 2, 3, 2, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3,
	4, 3, 4, 3, 4, 3, 5, 3, 5, 3, 5, 3, 5, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 3, 1, 1, 3, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1, 3,
	1, 3, 1, 3, 1, 4, 1, 4, 1, 4, 1, 4, 1, 2, 2, 2, 2, 2, 2, 3, 2, 3, 2, 3, 2,
	4, 2, 4, 2, 4, 2, 2, 2, 2, 5, 2, 2, 2, 2, 5, 2, 5, 2, 2, 5, 2, 2, 2, 2, 2,
	2, 5, 2, 2, 2, 2, 3, 2, 3, 2, 4, 2, 4, 2, 2, 5, 2, 2, 2, 5, 2, 2, 4, 5, 2,
	2, 3, 2, 4, 2, 5, 2, 4, 5, 4, 4, 4, 4, 4, 4, 4, 4, 6, 2, 2, 2, 2, 2, 2, 2,
	4, 4, 3, 5, 2, 3, 2, 1, 2, 1, 2, 1, 2, 1, 3, 1, 3, 1, 3, 1, 3, 1
};

void OpenGLMachine::CallFunction(GLFunctions::Type ID)
{
	switch(ID)
	{
	case GLFunctions::Accum:
		glAccum(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::ActiveShaderProgram:
		glActiveShaderProgram(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::ActiveTexture:
		glActiveTexture(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::AlphaFunc:
		glAlphaFunc(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::AreTexturesResident:
		glAreTexturesResident(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8),
			*reinterpret_cast<GLboolean **>(Registers+16)); break;
	case GLFunctions::ArrayElement:
		glArrayElement(*reinterpret_cast<GLint*>(Registers)); break;
	case GLFunctions::AttachShader:
		glAttachShader(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::Begin:
		glBegin(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::BeginConditionalRender:
		glBeginConditionalRender(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::BeginQuery:
		glBeginQuery(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::BeginQueryIndexed:
		glBeginQueryIndexed(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::BeginTransformFeedback:
		glBeginTransformFeedback(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::BindAttribLocation:
		glBindAttribLocation(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<const GLchar **>(Registers+16)); break;
	case GLFunctions::BindBuffer:
		glBindBuffer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::BindBufferBase:
		glBindBufferBase(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::BindBufferRange:
		glBindBufferRange(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLintptr*>(Registers+24),
			*reinterpret_cast<GLsizeiptr*>(Registers+32)); break;
	case GLFunctions::BindBuffersBase:
		glBindBuffersBase(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::BindBuffersRange:
		glBindBuffersRange(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24),
			*reinterpret_cast<const GLintptr **>(Registers+32),
			*reinterpret_cast<const GLsizeiptr **>(Registers+40)); break;
	case GLFunctions::BindFragDataLocation:
		glBindFragDataLocation(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<const GLchar **>(Registers+16)); break;
	case GLFunctions::BindFragDataLocationIndexed:
		glBindFragDataLocationIndexed(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<const GLchar **>(Registers+24)); break;
	case GLFunctions::BindFramebuffer:
		glBindFramebuffer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::BindImageTexture:
		glBindImageTexture(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLenum*>(Registers+40),
			*reinterpret_cast<GLenum*>(Registers+48)); break;
	case GLFunctions::BindImageTextures:
		glBindImageTextures(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::BindProgramPipeline:
		glBindProgramPipeline(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::BindRenderbuffer:
		glBindRenderbuffer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::BindSampler:
		glBindSampler(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::BindSamplers:
		glBindSamplers(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::BindTexture:
		glBindTexture(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::BindTextures:
		glBindTextures(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::BindTransformFeedback:
		glBindTransformFeedback(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::BindVertexArray:
		glBindVertexArray(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::BindVertexBuffer:
		glBindVertexBuffer(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLintptr*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::BindVertexBuffers:
		glBindVertexBuffers(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16),
			*reinterpret_cast<const GLintptr **>(Registers+24),
			*reinterpret_cast<const GLsizei **>(Registers+32)); break;
	case GLFunctions::Bitmap:
		glBitmap(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24),
			*reinterpret_cast<GLfloat*>(Registers+32),
			*reinterpret_cast<GLfloat*>(Registers+40),
			*reinterpret_cast<const GLubyte **>(Registers+48)); break;
	case GLFunctions::BlendColor:
		glBlendColor(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::BlendEquation:
		glBlendEquation(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::BlendEquationSeparate:
		glBlendEquationSeparate(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::BlendEquationSeparatei:
		glBlendEquationSeparatei(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16)); break;
	case GLFunctions::BlendEquationi:
		glBlendEquationi(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::BlendFunc:
		glBlendFunc(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::BlendFuncSeparate:
		glBlendFuncSeparate(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24)); break;
	case GLFunctions::BlendFuncSeparatei:
		glBlendFuncSeparatei(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<GLenum*>(Registers+32)); break;
	case GLFunctions::BlendFunci:
		glBlendFunci(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16)); break;
	case GLFunctions::BlitFramebuffer:
		glBlitFramebuffer(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40),
			*reinterpret_cast<GLint*>(Registers+48),
			*reinterpret_cast<GLint*>(Registers+56),
			*reinterpret_cast<GLbitfield*>(Registers+64),
			*reinterpret_cast<GLenum*>(Registers+72)); break;
	case GLFunctions::BufferData:
		glBufferData(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizeiptr*>(Registers+8),
			*reinterpret_cast<const GLvoid **>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24)); break;
	case GLFunctions::BufferStorage:
		glBufferStorage(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizeiptr*>(Registers+8),
			*reinterpret_cast<const void **>(Registers+16),
			*reinterpret_cast<GLbitfield*>(Registers+24)); break;
	case GLFunctions::BufferSubData:
		glBufferSubData(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLintptr*>(Registers+8),
			*reinterpret_cast<GLsizeiptr*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24)); break;
	case GLFunctions::CallList:
		glCallList(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::CallLists:
		glCallLists(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLvoid **>(Registers+16)); break;
	case GLFunctions::CheckFramebufferStatus:
		glCheckFramebufferStatus(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::ClampColor:
		glClampColor(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::Clear:
		glClear(*reinterpret_cast<GLbitfield*>(Registers)); break;
	case GLFunctions::ClearAccum:
		glClearAccum(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::ClearBufferData:
		glClearBufferData(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<const void **>(Registers+32)); break;
	case GLFunctions::ClearBufferSubData:
		glClearBufferSubData(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLintptr*>(Registers+16),
			*reinterpret_cast<GLsizeiptr*>(Registers+24),
			*reinterpret_cast<GLenum*>(Registers+32),
			*reinterpret_cast<GLenum*>(Registers+40),
			*reinterpret_cast<const void **>(Registers+48)); break;
	case GLFunctions::ClearBufferfi:
		glClearBufferfi(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::ClearBufferfv:
		glClearBufferfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::ClearBufferiv:
		glClearBufferiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::ClearBufferuiv:
		glClearBufferuiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::ClearColor:
		glClearColor(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::ClearDepth:
		glClearDepth(*reinterpret_cast<GLdouble*>(Registers)); break;
	case GLFunctions::ClearDepthf:
		glClearDepthf(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::ClearIndex:
		glClearIndex(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::ClearStencil:
		glClearStencil(*reinterpret_cast<GLint*>(Registers)); break;
	case GLFunctions::ClearTexImage:
		glClearTexImage(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<const void **>(Registers+32)); break;
	case GLFunctions::ClearTexSubImage:
		glClearTexSubImage(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLsizei*>(Registers+48),
			*reinterpret_cast<GLsizei*>(Registers+56),
			*reinterpret_cast<GLenum*>(Registers+64),
			*reinterpret_cast<GLenum*>(Registers+72),
			*reinterpret_cast<const void **>(Registers+80)); break;
	case GLFunctions::ClientActiveTexture:
		glClientActiveTexture(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::ClientWaitSync:
		glClientWaitSync(*reinterpret_cast<GLsync*>(Registers),
			*reinterpret_cast<GLbitfield*>(Registers+8),
			*reinterpret_cast<GLuint64*>(Registers+16)); break;
	case GLFunctions::ClipPlane:
		glClipPlane(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::Color3b:
		glColor3b(*reinterpret_cast<GLbyte*>(Registers),
			*reinterpret_cast<GLbyte*>(Registers+8),
			*reinterpret_cast<GLbyte*>(Registers+16)); break;
	case GLFunctions::Color3bv:
		glColor3bv(*reinterpret_cast<const GLbyte **>(Registers)); break;
	case GLFunctions::Color3d:
		glColor3d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::Color3dv:
		glColor3dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::Color3f:
		glColor3f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::Color3fv:
		glColor3fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::Color3i:
		glColor3i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::Color3iv:
		glColor3iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::Color3s:
		glColor3s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::Color3sv:
		glColor3sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::Color3ub:
		glColor3ub(*reinterpret_cast<GLubyte*>(Registers),
			*reinterpret_cast<GLubyte*>(Registers+8),
			*reinterpret_cast<GLubyte*>(Registers+16)); break;
	case GLFunctions::Color3ubv:
		glColor3ubv(*reinterpret_cast<const GLubyte **>(Registers)); break;
	case GLFunctions::Color3ui:
		glColor3ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::Color3uiv:
		glColor3uiv(*reinterpret_cast<const GLuint **>(Registers)); break;
	case GLFunctions::Color3us:
		glColor3us(*reinterpret_cast<GLushort*>(Registers),
			*reinterpret_cast<GLushort*>(Registers+8),
			*reinterpret_cast<GLushort*>(Registers+16)); break;
	case GLFunctions::Color3usv:
		glColor3usv(*reinterpret_cast<const GLushort **>(Registers)); break;
	case GLFunctions::Color4b:
		glColor4b(*reinterpret_cast<GLbyte*>(Registers),
			*reinterpret_cast<GLbyte*>(Registers+8),
			*reinterpret_cast<GLbyte*>(Registers+16),
			*reinterpret_cast<GLbyte*>(Registers+24)); break;
	case GLFunctions::Color4bv:
		glColor4bv(*reinterpret_cast<const GLbyte **>(Registers)); break;
	case GLFunctions::Color4d:
		glColor4d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::Color4dv:
		glColor4dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::Color4f:
		glColor4f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::Color4fv:
		glColor4fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::Color4i:
		glColor4i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::Color4iv:
		glColor4iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::Color4s:
		glColor4s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24)); break;
	case GLFunctions::Color4sv:
		glColor4sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::Color4ub:
		glColor4ub(*reinterpret_cast<GLubyte*>(Registers),
			*reinterpret_cast<GLubyte*>(Registers+8),
			*reinterpret_cast<GLubyte*>(Registers+16),
			*reinterpret_cast<GLubyte*>(Registers+24)); break;
	case GLFunctions::Color4ubv:
		glColor4ubv(*reinterpret_cast<const GLubyte **>(Registers)); break;
	case GLFunctions::Color4ui:
		glColor4ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::Color4uiv:
		glColor4uiv(*reinterpret_cast<const GLuint **>(Registers)); break;
	case GLFunctions::Color4us:
		glColor4us(*reinterpret_cast<GLushort*>(Registers),
			*reinterpret_cast<GLushort*>(Registers+8),
			*reinterpret_cast<GLushort*>(Registers+16),
			*reinterpret_cast<GLushort*>(Registers+24)); break;
	case GLFunctions::Color4usv:
		glColor4usv(*reinterpret_cast<const GLushort **>(Registers)); break;
	case GLFunctions::ColorMask:
		glColorMask(*reinterpret_cast<GLboolean*>(Registers),
			*reinterpret_cast<GLboolean*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24)); break;
	case GLFunctions::ColorMaski:
		glColorMaski(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLboolean*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<GLboolean*>(Registers+32)); break;
	case GLFunctions::ColorMaterial:
		glColorMaterial(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::ColorP3ui:
		glColorP3ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::ColorP3uiv:
		glColorP3uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::ColorP4ui:
		glColorP4ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::ColorP4uiv:
		glColorP4uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::ColorPointer:
		glColorPointer(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24)); break;
	case GLFunctions::CompileShader:
		glCompileShader(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::CompressedTexImage1D:
		glCompressedTexImage1D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<const GLvoid **>(Registers+48)); break;
	case GLFunctions::CompressedTexImage2D:
		glCompressedTexImage2D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40),
			*reinterpret_cast<GLsizei*>(Registers+48),
			*reinterpret_cast<const GLvoid **>(Registers+56)); break;
	case GLFunctions::CompressedTexImage3D:
		glCompressedTexImage3D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLint*>(Registers+48),
			*reinterpret_cast<GLsizei*>(Registers+56),
			*reinterpret_cast<const GLvoid **>(Registers+64)); break;
	case GLFunctions::CompressedTexSubImage1D:
		glCompressedTexSubImage1D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLenum*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<const GLvoid **>(Registers+48)); break;
	case GLFunctions::CompressedTexSubImage2D:
		glCompressedTexSubImage2D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLenum*>(Registers+48),
			*reinterpret_cast<GLsizei*>(Registers+56),
			*reinterpret_cast<const GLvoid **>(Registers+64)); break;
	case GLFunctions::CompressedTexSubImage3D:
		glCompressedTexSubImage3D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLsizei*>(Registers+48),
			*reinterpret_cast<GLsizei*>(Registers+56),
			*reinterpret_cast<GLenum*>(Registers+64),
			*reinterpret_cast<GLsizei*>(Registers+72),
			*reinterpret_cast<const GLvoid **>(Registers+80)); break;
	case GLFunctions::CopyBufferSubData:
		glCopyBufferSubData(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLintptr*>(Registers+16),
			*reinterpret_cast<GLintptr*>(Registers+24),
			*reinterpret_cast<GLsizeiptr*>(Registers+32)); break;
	case GLFunctions::CopyImageSubData:
		glCopyImageSubData(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40),
			*reinterpret_cast<GLuint*>(Registers+48),
			*reinterpret_cast<GLenum*>(Registers+56),
			*reinterpret_cast<GLint*>(Registers+64),
			*reinterpret_cast<GLint*>(Registers+72),
			*reinterpret_cast<GLint*>(Registers+80),
			*reinterpret_cast<GLint*>(Registers+88),
			*reinterpret_cast<GLsizei*>(Registers+96),
			*reinterpret_cast<GLsizei*>(Registers+104),
			*reinterpret_cast<GLsizei*>(Registers+112)); break;
	case GLFunctions::CopyPixels:
		glCopyPixels(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLenum*>(Registers+32)); break;
	case GLFunctions::CopyTexImage1D:
		glCopyTexImage1D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLint*>(Registers+48)); break;
	case GLFunctions::CopyTexImage2D:
		glCopyTexImage2D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLsizei*>(Registers+48),
			*reinterpret_cast<GLint*>(Registers+56)); break;
	case GLFunctions::CopyTexSubImage1D:
		glCopyTexSubImage1D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40)); break;
	case GLFunctions::CopyTexSubImage2D:
		glCopyTexSubImage2D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40),
			*reinterpret_cast<GLsizei*>(Registers+48),
			*reinterpret_cast<GLsizei*>(Registers+56)); break;
	case GLFunctions::CopyTexSubImage3D:
		glCopyTexSubImage3D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40),
			*reinterpret_cast<GLint*>(Registers+48),
			*reinterpret_cast<GLsizei*>(Registers+56),
			*reinterpret_cast<GLsizei*>(Registers+64)); break;
	case GLFunctions::CreateProgram:
		glCreateProgram(); break;
	case GLFunctions::CreateShader:
		glCreateShader(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::CreateShaderProgramv:
		glCreateShaderProgramv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLchar *const**>(Registers+16)); break;
	case GLFunctions::CullFace:
		glCullFace(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::DebugMessageCallback:
		glDebugMessageCallback(*reinterpret_cast<GLDEBUGPROC*>(Registers),
			*reinterpret_cast<const void **>(Registers+8)); break;
	case GLFunctions::DebugMessageControl:
		glDebugMessageControl(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<const GLuint **>(Registers+32),
			*reinterpret_cast<GLboolean*>(Registers+40)); break;
	case GLFunctions::DebugMessageInsert:
		glDebugMessageInsert(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<const GLchar **>(Registers+40)); break;
	case GLFunctions::DeleteBuffers:
		glDeleteBuffers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DeleteFramebuffers:
		glDeleteFramebuffers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DeleteLists:
		glDeleteLists(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8)); break;
	case GLFunctions::DeleteProgram:
		glDeleteProgram(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::DeleteProgramPipelines:
		glDeleteProgramPipelines(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DeleteQueries:
		glDeleteQueries(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DeleteRenderbuffers:
		glDeleteRenderbuffers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DeleteSamplers:
		glDeleteSamplers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DeleteShader:
		glDeleteShader(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::DeleteSync:
		glDeleteSync(*reinterpret_cast<GLsync*>(Registers)); break;
	case GLFunctions::DeleteTextures:
		glDeleteTextures(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DeleteTransformFeedbacks:
		glDeleteTransformFeedbacks(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DeleteVertexArrays:
		glDeleteVertexArrays(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::DepthFunc:
		glDepthFunc(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::DepthMask:
		glDepthMask(*reinterpret_cast<GLboolean*>(Registers)); break;
	case GLFunctions::DepthRange:
		glDepthRange(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::DepthRangeArrayv:
		glDepthRangeArrayv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLdouble **>(Registers+16)); break;
	case GLFunctions::DepthRangeIndexed:
		glDepthRangeIndexed(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::DepthRangef:
		glDepthRangef(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::DetachShader:
		glDetachShader(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::Disable:
		glDisable(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::DisableClientState:
		glDisableClientState(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::DisableVertexAttribArray:
		glDisableVertexAttribArray(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::Disablei:
		glDisablei(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::DispatchCompute:
		glDispatchCompute(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::DispatchComputeIndirect:
		glDispatchComputeIndirect(*reinterpret_cast<GLintptr*>(Registers)); break;
	case GLFunctions::DrawArrays:
		glDrawArrays(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16)); break;
	case GLFunctions::DrawArraysIndirect:
		glDrawArraysIndirect(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLvoid **>(Registers+8)); break;
	case GLFunctions::DrawArraysInstanced:
		glDrawArraysInstanced(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::DrawArraysInstancedBaseInstance:
		glDrawArraysInstancedBaseInstance(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLuint*>(Registers+32)); break;
	case GLFunctions::DrawBuffer:
		glDrawBuffer(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::DrawBuffers:
		glDrawBuffers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLenum **>(Registers+8)); break;
	case GLFunctions::DrawElements:
		glDrawElements(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24)); break;
	case GLFunctions::DrawElementsBaseVertex:
		glDrawElementsBaseVertex(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::DrawElementsIndirect:
		glDrawElementsIndirect(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLvoid **>(Registers+16)); break;
	case GLFunctions::DrawElementsInstanced:
		glDrawElementsInstanced(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32)); break;
	case GLFunctions::DrawElementsInstancedBaseInstance:
		glDrawElementsInstancedBaseInstance(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const void **>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLuint*>(Registers+40)); break;
	case GLFunctions::DrawElementsInstancedBaseVertex:
		glDrawElementsInstancedBaseVertex(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40)); break;
	case GLFunctions::DrawElementsInstancedBaseVertexBaseInstance:
		glDrawElementsInstancedBaseVertexBaseInstance(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const void **>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40),
			*reinterpret_cast<GLuint*>(Registers+48)); break;
	case GLFunctions::DrawPixels:
		glDrawPixels(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<const GLvoid **>(Registers+32)); break;
	case GLFunctions::DrawRangeElements:
		glDrawRangeElements(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLenum*>(Registers+32),
			*reinterpret_cast<const GLvoid **>(Registers+40)); break;
	case GLFunctions::DrawRangeElementsBaseVertex:
		glDrawRangeElementsBaseVertex(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLenum*>(Registers+32),
			*reinterpret_cast<const GLvoid **>(Registers+40),
			*reinterpret_cast<GLint*>(Registers+48)); break;
	case GLFunctions::DrawTransformFeedback:
		glDrawTransformFeedback(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::DrawTransformFeedbackInstanced:
		glDrawTransformFeedbackInstanced(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16)); break;
	case GLFunctions::DrawTransformFeedbackStream:
		glDrawTransformFeedbackStream(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::DrawTransformFeedbackStreamInstanced:
		glDrawTransformFeedbackStreamInstanced(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::EdgeFlag:
		glEdgeFlag(*reinterpret_cast<GLboolean*>(Registers)); break;
	case GLFunctions::EdgeFlagPointer:
		glEdgeFlagPointer(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLvoid **>(Registers+8)); break;
	case GLFunctions::EdgeFlagv:
		glEdgeFlagv(*reinterpret_cast<const GLboolean **>(Registers)); break;
	case GLFunctions::Enable:
		glEnable(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::EnableClientState:
		glEnableClientState(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::EnableVertexAttribArray:
		glEnableVertexAttribArray(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::Enablei:
		glEnablei(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::End:
		glEnd(); break;
	case GLFunctions::EndConditionalRender:
		glEndConditionalRender(); break;
	case GLFunctions::EndList:
		glEndList(); break;
	case GLFunctions::EndQuery:
		glEndQuery(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::EndQueryIndexed:
		glEndQueryIndexed(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::EndTransformFeedback:
		glEndTransformFeedback(); break;
	case GLFunctions::EvalCoord1d:
		glEvalCoord1d(*reinterpret_cast<GLdouble*>(Registers)); break;
	case GLFunctions::EvalCoord1dv:
		glEvalCoord1dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::EvalCoord1f:
		glEvalCoord1f(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::EvalCoord1fv:
		glEvalCoord1fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::EvalCoord2d:
		glEvalCoord2d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::EvalCoord2dv:
		glEvalCoord2dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::EvalCoord2f:
		glEvalCoord2f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::EvalCoord2fv:
		glEvalCoord2fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::EvalMesh1:
		glEvalMesh1(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::EvalMesh2:
		glEvalMesh2(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::EvalPoint1:
		glEvalPoint1(*reinterpret_cast<GLint*>(Registers)); break;
	case GLFunctions::EvalPoint2:
		glEvalPoint2(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::FeedbackBuffer:
		glFeedbackBuffer(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::FenceSync:
		glFenceSync(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLbitfield*>(Registers+8)); break;
	case GLFunctions::Finish:
		glFinish(); break;
	case GLFunctions::Flush:
		glFlush(); break;
	case GLFunctions::FlushMappedBufferRange:
		glFlushMappedBufferRange(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLintptr*>(Registers+8),
			*reinterpret_cast<GLsizeiptr*>(Registers+16)); break;
	case GLFunctions::FogCoordPointer:
		glFogCoordPointer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLvoid **>(Registers+16)); break;
	case GLFunctions::FogCoordd:
		glFogCoordd(*reinterpret_cast<GLdouble*>(Registers)); break;
	case GLFunctions::FogCoorddv:
		glFogCoorddv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::FogCoordf:
		glFogCoordf(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::FogCoordfv:
		glFogCoordfv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::Fogf:
		glFogf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::Fogfv:
		glFogfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::Fogi:
		glFogi(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::Fogiv:
		glFogiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::FramebufferParameteri:
		glFramebufferParameteri(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::FramebufferRenderbuffer:
		glFramebufferRenderbuffer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::FramebufferTexture:
		glFramebufferTexture(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::FramebufferTexture1D:
		glFramebufferTexture1D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::FramebufferTexture2D:
		glFramebufferTexture2D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::FramebufferTexture3D:
		glFramebufferTexture3D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40)); break;
	case GLFunctions::FramebufferTextureLayer:
		glFramebufferTextureLayer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::FrontFace:
		glFrontFace(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::Frustum:
		glFrustum(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32),
			*reinterpret_cast<GLdouble*>(Registers+40)); break;
	case GLFunctions::GenBuffers:
		glGenBuffers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenFramebuffers:
		glGenFramebuffers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenLists:
		glGenLists(*reinterpret_cast<GLsizei*>(Registers)); break;
	case GLFunctions::GenProgramPipelines:
		glGenProgramPipelines(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenQueries:
		glGenQueries(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenRenderbuffers:
		glGenRenderbuffers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenSamplers:
		glGenSamplers(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenTextures:
		glGenTextures(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenTransformFeedbacks:
		glGenTransformFeedbacks(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenVertexArrays:
		glGenVertexArrays(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GenerateMipmap:
		glGenerateMipmap(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::GetActiveAtomicCounterBufferiv:
		glGetActiveAtomicCounterBufferiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint **>(Registers+24)); break;
	case GLFunctions::GetActiveAttrib:
		glGetActiveAttrib(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei **>(Registers+24),
			*reinterpret_cast<GLint **>(Registers+32),
			*reinterpret_cast<GLenum **>(Registers+40),
			*reinterpret_cast<GLchar **>(Registers+48)); break;
	case GLFunctions::GetActiveSubroutineName:
		glGetActiveSubroutineName(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei **>(Registers+32),
			*reinterpret_cast<GLchar **>(Registers+40)); break;
	case GLFunctions::GetActiveSubroutineUniformName:
		glGetActiveSubroutineUniformName(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei **>(Registers+32),
			*reinterpret_cast<GLchar **>(Registers+40)); break;
	case GLFunctions::GetActiveSubroutineUniformiv:
		glGetActiveSubroutineUniformiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<GLint **>(Registers+32)); break;
	case GLFunctions::GetActiveUniform:
		glGetActiveUniform(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei **>(Registers+24),
			*reinterpret_cast<GLint **>(Registers+32),
			*reinterpret_cast<GLenum **>(Registers+40),
			*reinterpret_cast<GLchar **>(Registers+48)); break;
	case GLFunctions::GetActiveUniformBlockName:
		glGetActiveUniformBlockName(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei **>(Registers+24),
			*reinterpret_cast<GLchar **>(Registers+32)); break;
	case GLFunctions::GetActiveUniformBlockiv:
		glGetActiveUniformBlockiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint **>(Registers+24)); break;
	case GLFunctions::GetActiveUniformName:
		glGetActiveUniformName(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei **>(Registers+24),
			*reinterpret_cast<GLchar **>(Registers+32)); break;
	case GLFunctions::GetActiveUniformsiv:
		glGetActiveUniformsiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<GLint **>(Registers+32)); break;
	case GLFunctions::GetAttachedShaders:
		glGetAttachedShaders(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLsizei **>(Registers+16),
			*reinterpret_cast<GLuint **>(Registers+24)); break;
	case GLFunctions::GetAttribLocation:
		glGetAttribLocation(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLchar **>(Registers+8)); break;
	case GLFunctions::GetBooleani_v:
		glGetBooleani_v(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLboolean **>(Registers+16)); break;
	case GLFunctions::GetBooleanv:
		glGetBooleanv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLboolean **>(Registers+8)); break;
	case GLFunctions::GetBufferParameteri64v:
		glGetBufferParameteri64v(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint64 **>(Registers+16)); break;
	case GLFunctions::GetBufferParameteriv:
		glGetBufferParameteriv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetBufferPointerv:
		glGetBufferPointerv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLvoid ***>(Registers+16)); break;
	case GLFunctions::GetBufferSubData:
		glGetBufferSubData(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLintptr*>(Registers+8),
			*reinterpret_cast<GLsizeiptr*>(Registers+16),
			*reinterpret_cast<GLvoid **>(Registers+24)); break;
	case GLFunctions::GetClipPlane:
		glGetClipPlane(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLdouble **>(Registers+8)); break;
	case GLFunctions::GetCompressedTexImage:
		glGetCompressedTexImage(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLvoid **>(Registers+16)); break;
	case GLFunctions::GetDebugMessageLog:
		glGetDebugMessageLog(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum **>(Registers+16),
			*reinterpret_cast<GLenum **>(Registers+24),
			*reinterpret_cast<GLuint **>(Registers+32),
			*reinterpret_cast<GLenum **>(Registers+40),
			*reinterpret_cast<GLsizei **>(Registers+48),
			*reinterpret_cast<GLchar **>(Registers+56)); break;
	case GLFunctions::GetDoublei_v:
		glGetDoublei_v(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLdouble **>(Registers+16)); break;
	case GLFunctions::GetDoublev:
		glGetDoublev(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLdouble **>(Registers+8)); break;
	case GLFunctions::GetError:
		glGetError(); break;
	case GLFunctions::GetFloati_v:
		glGetFloati_v(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetFloatv:
		glGetFloatv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat **>(Registers+8)); break;
	case GLFunctions::GetFragDataIndex:
		glGetFragDataIndex(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLchar **>(Registers+8)); break;
	case GLFunctions::GetFragDataLocation:
		glGetFragDataLocation(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLchar **>(Registers+8)); break;
	case GLFunctions::GetFramebufferAttachmentParameteriv:
		glGetFramebufferAttachmentParameteriv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint **>(Registers+24)); break;
	case GLFunctions::GetFramebufferParameteriv:
		glGetFramebufferParameteriv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetInteger64i_v:
		glGetInteger64i_v(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLint64 **>(Registers+16)); break;
	case GLFunctions::GetInteger64v:
		glGetInteger64v(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint64 **>(Registers+8)); break;
	case GLFunctions::GetIntegeri_v:
		glGetIntegeri_v(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetIntegerv:
		glGetIntegerv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint **>(Registers+8)); break;
	case GLFunctions::GetInternalformati64v:
		glGetInternalformati64v(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLint64 **>(Registers+32)); break;
	case GLFunctions::GetInternalformativ:
		glGetInternalformativ(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLint **>(Registers+32)); break;
	case GLFunctions::GetLightfv:
		glGetLightfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetLightiv:
		glGetLightiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetMapdv:
		glGetMapdv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLdouble **>(Registers+16)); break;
	case GLFunctions::GetMapfv:
		glGetMapfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetMapiv:
		glGetMapiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetMaterialfv:
		glGetMaterialfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetMaterialiv:
		glGetMaterialiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetMultisamplefv:
		glGetMultisamplefv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetObjectLabel:
		glGetObjectLabel(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei **>(Registers+24),
			*reinterpret_cast<GLchar **>(Registers+32)); break;
	case GLFunctions::GetObjectPtrLabel:
		glGetObjectPtrLabel(*reinterpret_cast<const void **>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLsizei **>(Registers+16),
			*reinterpret_cast<GLchar **>(Registers+24)); break;
	case GLFunctions::GetPixelMapfv:
		glGetPixelMapfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat **>(Registers+8)); break;
	case GLFunctions::GetPixelMapuiv:
		glGetPixelMapuiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::GetPixelMapusv:
		glGetPixelMapusv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLushort **>(Registers+8)); break;
	case GLFunctions::GetPointerv:
		glGetPointerv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLvoid ***>(Registers+8)); break;
	case GLFunctions::GetPolygonStipple:
		glGetPolygonStipple(*reinterpret_cast<GLubyte **>(Registers)); break;
	case GLFunctions::GetProgramBinary:
		glGetProgramBinary(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLsizei **>(Registers+16),
			*reinterpret_cast<GLenum **>(Registers+24),
			*reinterpret_cast<GLvoid **>(Registers+32)); break;
	case GLFunctions::GetProgramInfoLog:
		glGetProgramInfoLog(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLsizei **>(Registers+16),
			*reinterpret_cast<GLchar **>(Registers+24)); break;
	case GLFunctions::GetProgramInterfaceiv:
		glGetProgramInterfaceiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint **>(Registers+24)); break;
	case GLFunctions::GetProgramPipelineInfoLog:
		glGetProgramPipelineInfoLog(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLsizei **>(Registers+16),
			*reinterpret_cast<GLchar **>(Registers+24)); break;
	case GLFunctions::GetProgramPipelineiv:
		glGetProgramPipelineiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetProgramResourceIndex:
		glGetProgramResourceIndex(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLchar **>(Registers+16)); break;
	case GLFunctions::GetProgramResourceLocation:
		glGetProgramResourceLocation(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLchar **>(Registers+16)); break;
	case GLFunctions::GetProgramResourceLocationIndex:
		glGetProgramResourceLocationIndex(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLchar **>(Registers+16)); break;
	case GLFunctions::GetProgramResourceName:
		glGetProgramResourceName(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei **>(Registers+32),
			*reinterpret_cast<GLchar **>(Registers+40)); break;
	case GLFunctions::GetProgramResourceiv:
		glGetProgramResourceiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<const GLenum **>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLsizei **>(Registers+48),
			*reinterpret_cast<GLint **>(Registers+56)); break;
	case GLFunctions::GetProgramStageiv:
		glGetProgramStageiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint **>(Registers+24)); break;
	case GLFunctions::GetProgramiv:
		glGetProgramiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetQueryIndexediv:
		glGetQueryIndexediv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint **>(Registers+24)); break;
	case GLFunctions::GetQueryObjecti64v:
		glGetQueryObjecti64v(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint64 **>(Registers+16)); break;
	case GLFunctions::GetQueryObjectiv:
		glGetQueryObjectiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetQueryObjectui64v:
		glGetQueryObjectui64v(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint64 **>(Registers+16)); break;
	case GLFunctions::GetQueryObjectuiv:
		glGetQueryObjectuiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint **>(Registers+16)); break;
	case GLFunctions::GetQueryiv:
		glGetQueryiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetRenderbufferParameteriv:
		glGetRenderbufferParameteriv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetSamplerParameterIiv:
		glGetSamplerParameterIiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetSamplerParameterIuiv:
		glGetSamplerParameterIuiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint **>(Registers+16)); break;
	case GLFunctions::GetSamplerParameterfv:
		glGetSamplerParameterfv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetSamplerParameteriv:
		glGetSamplerParameteriv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetShaderInfoLog:
		glGetShaderInfoLog(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLsizei **>(Registers+16),
			*reinterpret_cast<GLchar **>(Registers+24)); break;
	case GLFunctions::GetShaderPrecisionFormat:
		glGetShaderPrecisionFormat(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16),
			*reinterpret_cast<GLint **>(Registers+24)); break;
	case GLFunctions::GetShaderSource:
		glGetShaderSource(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLsizei **>(Registers+16),
			*reinterpret_cast<GLchar **>(Registers+24)); break;
	case GLFunctions::GetShaderiv:
		glGetShaderiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetString:
		glGetString(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::GetStringi:
		glGetStringi(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::GetSubroutineIndex:
		glGetSubroutineIndex(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLchar **>(Registers+16)); break;
	case GLFunctions::GetSubroutineUniformLocation:
		glGetSubroutineUniformLocation(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLchar **>(Registers+16)); break;
	case GLFunctions::GetSynciv:
		glGetSynciv(*reinterpret_cast<GLsync*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei **>(Registers+24),
			*reinterpret_cast<GLint **>(Registers+32)); break;
	case GLFunctions::GetTexEnvfv:
		glGetTexEnvfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetTexEnviv:
		glGetTexEnviv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetTexGendv:
		glGetTexGendv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLdouble **>(Registers+16)); break;
	case GLFunctions::GetTexGenfv:
		glGetTexGenfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetTexGeniv:
		glGetTexGeniv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetTexImage:
		glGetTexImage(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<GLvoid **>(Registers+32)); break;
	case GLFunctions::GetTexLevelParameterfv:
		glGetTexLevelParameterfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLfloat **>(Registers+24)); break;
	case GLFunctions::GetTexLevelParameteriv:
		glGetTexLevelParameteriv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLint **>(Registers+24)); break;
	case GLFunctions::GetTexParameterIiv:
		glGetTexParameterIiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetTexParameterIuiv:
		glGetTexParameterIuiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint **>(Registers+16)); break;
	case GLFunctions::GetTexParameterfv:
		glGetTexParameterfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetTexParameteriv:
		glGetTexParameteriv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetTransformFeedbackVarying:
		glGetTransformFeedbackVarying(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei **>(Registers+24),
			*reinterpret_cast<GLsizei **>(Registers+32),
			*reinterpret_cast<GLenum **>(Registers+40),
			*reinterpret_cast<GLchar **>(Registers+48)); break;
	case GLFunctions::GetUniformBlockIndex:
		glGetUniformBlockIndex(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLchar **>(Registers+8)); break;
	case GLFunctions::GetUniformIndices:
		glGetUniformIndices(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLchar *const**>(Registers+16),
			*reinterpret_cast<GLuint **>(Registers+24)); break;
	case GLFunctions::GetUniformLocation:
		glGetUniformLocation(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLchar **>(Registers+8)); break;
	case GLFunctions::GetUniformSubroutineuiv:
		glGetUniformSubroutineuiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLuint **>(Registers+16)); break;
	case GLFunctions::GetUniformdv:
		glGetUniformdv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLdouble **>(Registers+16)); break;
	case GLFunctions::GetUniformfv:
		glGetUniformfv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetUniformiv:
		glGetUniformiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetUniformuiv:
		glGetUniformuiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLuint **>(Registers+16)); break;
	case GLFunctions::GetVertexAttribIiv:
		glGetVertexAttribIiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::GetVertexAttribIuiv:
		glGetVertexAttribIuiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint **>(Registers+16)); break;
	case GLFunctions::GetVertexAttribLdv:
		glGetVertexAttribLdv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLdouble **>(Registers+16)); break;
	case GLFunctions::GetVertexAttribPointerv:
		glGetVertexAttribPointerv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLvoid ***>(Registers+16)); break;
	case GLFunctions::GetVertexAttribdv:
		glGetVertexAttribdv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLdouble **>(Registers+16)); break;
	case GLFunctions::GetVertexAttribfv:
		glGetVertexAttribfv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat **>(Registers+16)); break;
	case GLFunctions::GetVertexAttribiv:
		glGetVertexAttribiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint **>(Registers+16)); break;
	case GLFunctions::Hint:
		glHint(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::IndexMask:
		glIndexMask(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IndexPointer:
		glIndexPointer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLvoid **>(Registers+16)); break;
	case GLFunctions::Indexd:
		glIndexd(*reinterpret_cast<GLdouble*>(Registers)); break;
	case GLFunctions::Indexdv:
		glIndexdv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::Indexf:
		glIndexf(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::Indexfv:
		glIndexfv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::Indexi:
		glIndexi(*reinterpret_cast<GLint*>(Registers)); break;
	case GLFunctions::Indexiv:
		glIndexiv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::Indexs:
		glIndexs(*reinterpret_cast<GLshort*>(Registers)); break;
	case GLFunctions::Indexsv:
		glIndexsv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::Indexub:
		glIndexub(*reinterpret_cast<GLubyte*>(Registers)); break;
	case GLFunctions::Indexubv:
		glIndexubv(*reinterpret_cast<const GLubyte **>(Registers)); break;
	case GLFunctions::InitNames:
		glInitNames(); break;
	case GLFunctions::InterleavedArrays:
		glInterleavedArrays(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLvoid **>(Registers+16)); break;
	case GLFunctions::InvalidateBufferData:
		glInvalidateBufferData(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::InvalidateBufferSubData:
		glInvalidateBufferSubData(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLintptr*>(Registers+8),
			*reinterpret_cast<GLsizeiptr*>(Registers+16)); break;
	case GLFunctions::InvalidateFramebuffer:
		glInvalidateFramebuffer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLenum **>(Registers+16)); break;
	case GLFunctions::InvalidateSubFramebuffer:
		glInvalidateSubFramebuffer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLenum **>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLsizei*>(Registers+48)); break;
	case GLFunctions::InvalidateTexImage:
		glInvalidateTexImage(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::InvalidateTexSubImage:
		glInvalidateTexSubImage(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLsizei*>(Registers+48),
			*reinterpret_cast<GLsizei*>(Registers+56)); break;
	case GLFunctions::IsBuffer:
		glIsBuffer(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsEnabled:
		glIsEnabled(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::IsEnabledi:
		glIsEnabledi(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::IsFramebuffer:
		glIsFramebuffer(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsList:
		glIsList(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsProgram:
		glIsProgram(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsProgramPipeline:
		glIsProgramPipeline(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsQuery:
		glIsQuery(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsRenderbuffer:
		glIsRenderbuffer(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsSampler:
		glIsSampler(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsShader:
		glIsShader(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsSync:
		glIsSync(*reinterpret_cast<GLsync*>(Registers)); break;
	case GLFunctions::IsTexture:
		glIsTexture(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsTransformFeedback:
		glIsTransformFeedback(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::IsVertexArray:
		glIsVertexArray(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::LightModelf:
		glLightModelf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::LightModelfv:
		glLightModelfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::LightModeli:
		glLightModeli(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::LightModeliv:
		glLightModeliv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::Lightf:
		glLightf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::Lightfv:
		glLightfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::Lighti:
		glLighti(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::Lightiv:
		glLightiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::LineStipple:
		glLineStipple(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLushort*>(Registers+8)); break;
	case GLFunctions::LineWidth:
		glLineWidth(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::LinkProgram:
		glLinkProgram(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::ListBase:
		glListBase(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::LoadIdentity:
		glLoadIdentity(); break;
	case GLFunctions::LoadMatrixd:
		glLoadMatrixd(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::LoadMatrixf:
		glLoadMatrixf(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::LoadName:
		glLoadName(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::LoadTransposeMatrixd:
		glLoadTransposeMatrixd(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::LoadTransposeMatrixf:
		glLoadTransposeMatrixf(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::LogicOp:
		glLogicOp(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::Map1d:
		glMap1d(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<const GLdouble **>(Registers+40)); break;
	case GLFunctions::Map1f:
		glMap1f(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<const GLfloat **>(Registers+40)); break;
	case GLFunctions::Map2d:
		glMap2d(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLdouble*>(Registers+40),
			*reinterpret_cast<GLdouble*>(Registers+48),
			*reinterpret_cast<GLint*>(Registers+56),
			*reinterpret_cast<GLint*>(Registers+64),
			*reinterpret_cast<const GLdouble **>(Registers+72)); break;
	case GLFunctions::Map2f:
		glMap2f(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLfloat*>(Registers+40),
			*reinterpret_cast<GLfloat*>(Registers+48),
			*reinterpret_cast<GLint*>(Registers+56),
			*reinterpret_cast<GLint*>(Registers+64),
			*reinterpret_cast<const GLfloat **>(Registers+72)); break;
	case GLFunctions::MapBuffer:
		glMapBuffer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::MapBufferRange:
		glMapBufferRange(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLintptr*>(Registers+8),
			*reinterpret_cast<GLsizeiptr*>(Registers+16),
			*reinterpret_cast<GLbitfield*>(Registers+24)); break;
	case GLFunctions::MapGrid1d:
		glMapGrid1d(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::MapGrid1f:
		glMapGrid1f(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::MapGrid2d:
		glMapGrid2d(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32),
			*reinterpret_cast<GLdouble*>(Registers+40)); break;
	case GLFunctions::MapGrid2f:
		glMapGrid2f(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLfloat*>(Registers+32),
			*reinterpret_cast<GLfloat*>(Registers+40)); break;
	case GLFunctions::Materialf:
		glMaterialf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::Materialfv:
		glMaterialfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::Materiali:
		glMateriali(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::Materialiv:
		glMaterialiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::MatrixMode:
		glMatrixMode(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::MemoryBarrier:
		glMemoryBarrier(*reinterpret_cast<GLbitfield*>(Registers)); break;
	case GLFunctions::MinSampleShading:
		glMinSampleShading(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::MultMatrixd:
		glMultMatrixd(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::MultMatrixf:
		glMultMatrixf(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::MultTransposeMatrixd:
		glMultTransposeMatrixd(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::MultTransposeMatrixf:
		glMultTransposeMatrixf(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::MultiDrawArrays:
		glMultiDrawArrays(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8),
			*reinterpret_cast<const GLsizei **>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::MultiDrawArraysIndirect:
		glMultiDrawArraysIndirect(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const void **>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::MultiDrawElements:
		glMultiDrawElements(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLsizei **>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const GLvoid *const**>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32)); break;
	case GLFunctions::MultiDrawElementsBaseVertex:
		glMultiDrawElementsBaseVertex(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLsizei **>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const GLvoid *const**>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<const GLint **>(Registers+40)); break;
	case GLFunctions::MultiDrawElementsIndirect:
		glMultiDrawElementsIndirect(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const void **>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32)); break;
	case GLFunctions::MultiTexCoord1d:
		glMultiTexCoord1d(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::MultiTexCoord1dv:
		glMultiTexCoord1dv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord1f:
		glMultiTexCoord1f(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::MultiTexCoord1fv:
		glMultiTexCoord1fv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord1i:
		glMultiTexCoord1i(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::MultiTexCoord1iv:
		glMultiTexCoord1iv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord1s:
		glMultiTexCoord1s(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8)); break;
	case GLFunctions::MultiTexCoord1sv:
		glMultiTexCoord1sv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord2d:
		glMultiTexCoord2d(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::MultiTexCoord2dv:
		glMultiTexCoord2dv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord2f:
		glMultiTexCoord2f(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::MultiTexCoord2fv:
		glMultiTexCoord2fv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord2i:
		glMultiTexCoord2i(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::MultiTexCoord2iv:
		glMultiTexCoord2iv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord2s:
		glMultiTexCoord2s(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::MultiTexCoord2sv:
		glMultiTexCoord2sv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord3d:
		glMultiTexCoord3d(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::MultiTexCoord3dv:
		glMultiTexCoord3dv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord3f:
		glMultiTexCoord3f(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::MultiTexCoord3fv:
		glMultiTexCoord3fv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord3i:
		glMultiTexCoord3i(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::MultiTexCoord3iv:
		glMultiTexCoord3iv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord3s:
		glMultiTexCoord3s(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24)); break;
	case GLFunctions::MultiTexCoord3sv:
		glMultiTexCoord3sv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord4d:
		glMultiTexCoord4d(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32)); break;
	case GLFunctions::MultiTexCoord4dv:
		glMultiTexCoord4dv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord4f:
		glMultiTexCoord4f(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24),
			*reinterpret_cast<GLfloat*>(Registers+32)); break;
	case GLFunctions::MultiTexCoord4fv:
		glMultiTexCoord4fv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord4i:
		glMultiTexCoord4i(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::MultiTexCoord4iv:
		glMultiTexCoord4iv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::MultiTexCoord4s:
		glMultiTexCoord4s(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24),
			*reinterpret_cast<GLshort*>(Registers+32)); break;
	case GLFunctions::MultiTexCoord4sv:
		glMultiTexCoord4sv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::MultiTexCoordP1ui:
		glMultiTexCoordP1ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::MultiTexCoordP1uiv:
		glMultiTexCoordP1uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::MultiTexCoordP2ui:
		glMultiTexCoordP2ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::MultiTexCoordP2uiv:
		glMultiTexCoordP2uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::MultiTexCoordP3ui:
		glMultiTexCoordP3ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::MultiTexCoordP3uiv:
		glMultiTexCoordP3uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::MultiTexCoordP4ui:
		glMultiTexCoordP4ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::MultiTexCoordP4uiv:
		glMultiTexCoordP4uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::NewList:
		glNewList(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::Normal3b:
		glNormal3b(*reinterpret_cast<GLbyte*>(Registers),
			*reinterpret_cast<GLbyte*>(Registers+8),
			*reinterpret_cast<GLbyte*>(Registers+16)); break;
	case GLFunctions::Normal3bv:
		glNormal3bv(*reinterpret_cast<const GLbyte **>(Registers)); break;
	case GLFunctions::Normal3d:
		glNormal3d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::Normal3dv:
		glNormal3dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::Normal3f:
		glNormal3f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::Normal3fv:
		glNormal3fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::Normal3i:
		glNormal3i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::Normal3iv:
		glNormal3iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::Normal3s:
		glNormal3s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::Normal3sv:
		glNormal3sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::NormalP3ui:
		glNormalP3ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::NormalP3uiv:
		glNormalP3uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::NormalPointer:
		glNormalPointer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLvoid **>(Registers+16)); break;
	case GLFunctions::ObjectLabel:
		glObjectLabel(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLchar **>(Registers+24)); break;
	case GLFunctions::ObjectPtrLabel:
		glObjectPtrLabel(*reinterpret_cast<const void **>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLchar **>(Registers+16)); break;
	case GLFunctions::Ortho:
		glOrtho(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32),
			*reinterpret_cast<GLdouble*>(Registers+40)); break;
	case GLFunctions::PassThrough:
		glPassThrough(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::PatchParameterfv:
		glPatchParameterfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::PatchParameteri:
		glPatchParameteri(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::PauseTransformFeedback:
		glPauseTransformFeedback(); break;
	case GLFunctions::PixelMapfv:
		glPixelMapfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::PixelMapuiv:
		glPixelMapuiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::PixelMapusv:
		glPixelMapusv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLushort **>(Registers+16)); break;
	case GLFunctions::PixelStoref:
		glPixelStoref(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::PixelStorei:
		glPixelStorei(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::PixelTransferf:
		glPixelTransferf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::PixelTransferi:
		glPixelTransferi(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::PixelZoom:
		glPixelZoom(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::PointParameterf:
		glPointParameterf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::PointParameterfv:
		glPointParameterfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::PointParameteri:
		glPointParameteri(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::PointParameteriv:
		glPointParameteriv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::PointSize:
		glPointSize(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::PolygonMode:
		glPolygonMode(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::PolygonOffset:
		glPolygonOffset(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::PolygonStipple:
		glPolygonStipple(*reinterpret_cast<const GLubyte **>(Registers)); break;
	case GLFunctions::PopAttrib:
		glPopAttrib(); break;
	case GLFunctions::PopClientAttrib:
		glPopClientAttrib(); break;
	case GLFunctions::PopDebugGroup:
		glPopDebugGroup(); break;
	case GLFunctions::PopMatrix:
		glPopMatrix(); break;
	case GLFunctions::PopName:
		glPopName(); break;
	case GLFunctions::PrimitiveRestartIndex:
		glPrimitiveRestartIndex(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::PrioritizeTextures:
		glPrioritizeTextures(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::ProgramBinary:
		glProgramBinary(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLvoid **>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::ProgramParameteri:
		glProgramParameteri(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::ProgramUniform1d:
		glProgramUniform1d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::ProgramUniform1dv:
		glProgramUniform1dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::ProgramUniform1f:
		glProgramUniform1f(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::ProgramUniform1fv:
		glProgramUniform1fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::ProgramUniform1i:
		glProgramUniform1i(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::ProgramUniform1iv:
		glProgramUniform1iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLint **>(Registers+24)); break;
	case GLFunctions::ProgramUniform1ui:
		glProgramUniform1ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::ProgramUniform1uiv:
		glProgramUniform1uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::ProgramUniform2d:
		glProgramUniform2d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::ProgramUniform2dv:
		glProgramUniform2dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::ProgramUniform2f:
		glProgramUniform2f(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::ProgramUniform2fv:
		glProgramUniform2fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::ProgramUniform2i:
		glProgramUniform2i(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::ProgramUniform2iv:
		glProgramUniform2iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLint **>(Registers+24)); break;
	case GLFunctions::ProgramUniform2ui:
		glProgramUniform2ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::ProgramUniform2uiv:
		glProgramUniform2uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::ProgramUniform3d:
		glProgramUniform3d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32)); break;
	case GLFunctions::ProgramUniform3dv:
		glProgramUniform3dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::ProgramUniform3f:
		glProgramUniform3f(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24),
			*reinterpret_cast<GLfloat*>(Registers+32)); break;
	case GLFunctions::ProgramUniform3fv:
		glProgramUniform3fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::ProgramUniform3i:
		glProgramUniform3i(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::ProgramUniform3iv:
		glProgramUniform3iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLint **>(Registers+24)); break;
	case GLFunctions::ProgramUniform3ui:
		glProgramUniform3ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24),
			*reinterpret_cast<GLuint*>(Registers+32)); break;
	case GLFunctions::ProgramUniform3uiv:
		glProgramUniform3uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::ProgramUniform4d:
		glProgramUniform4d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32),
			*reinterpret_cast<GLdouble*>(Registers+40)); break;
	case GLFunctions::ProgramUniform4dv:
		glProgramUniform4dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::ProgramUniform4f:
		glProgramUniform4f(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24),
			*reinterpret_cast<GLfloat*>(Registers+32),
			*reinterpret_cast<GLfloat*>(Registers+40)); break;
	case GLFunctions::ProgramUniform4fv:
		glProgramUniform4fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::ProgramUniform4i:
		glProgramUniform4i(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40)); break;
	case GLFunctions::ProgramUniform4iv:
		glProgramUniform4iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLint **>(Registers+24)); break;
	case GLFunctions::ProgramUniform4ui:
		glProgramUniform4ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24),
			*reinterpret_cast<GLuint*>(Registers+32),
			*reinterpret_cast<GLuint*>(Registers+40)); break;
	case GLFunctions::ProgramUniform4uiv:
		glProgramUniform4uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::ProgramUniformMatrix2dv:
		glProgramUniformMatrix2dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix2fv:
		glProgramUniformMatrix2fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix2x3dv:
		glProgramUniformMatrix2x3dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix2x3fv:
		glProgramUniformMatrix2x3fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix2x4dv:
		glProgramUniformMatrix2x4dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix2x4fv:
		glProgramUniformMatrix2x4fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix3dv:
		glProgramUniformMatrix3dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix3fv:
		glProgramUniformMatrix3fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix3x2dv:
		glProgramUniformMatrix3x2dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix3x2fv:
		glProgramUniformMatrix3x2fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix3x4dv:
		glProgramUniformMatrix3x4dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix3x4fv:
		glProgramUniformMatrix3x4fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix4dv:
		glProgramUniformMatrix4dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix4fv:
		glProgramUniformMatrix4fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix4x2dv:
		glProgramUniformMatrix4x2dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix4x2fv:
		glProgramUniformMatrix4x2fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix4x3dv:
		glProgramUniformMatrix4x3dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLdouble **>(Registers+32)); break;
	case GLFunctions::ProgramUniformMatrix4x3fv:
		glProgramUniformMatrix4x3fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<const GLfloat **>(Registers+32)); break;
	case GLFunctions::ProvokingVertex:
		glProvokingVertex(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::PushAttrib:
		glPushAttrib(*reinterpret_cast<GLbitfield*>(Registers)); break;
	case GLFunctions::PushClientAttrib:
		glPushClientAttrib(*reinterpret_cast<GLbitfield*>(Registers)); break;
	case GLFunctions::PushDebugGroup:
		glPushDebugGroup(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLchar **>(Registers+24)); break;
	case GLFunctions::PushMatrix:
		glPushMatrix(); break;
	case GLFunctions::PushName:
		glPushName(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::QueryCounter:
		glQueryCounter(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8)); break;
	case GLFunctions::RasterPos2d:
		glRasterPos2d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::RasterPos2dv:
		glRasterPos2dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::RasterPos2f:
		glRasterPos2f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::RasterPos2fv:
		glRasterPos2fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::RasterPos2i:
		glRasterPos2i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::RasterPos2iv:
		glRasterPos2iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::RasterPos2s:
		glRasterPos2s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8)); break;
	case GLFunctions::RasterPos2sv:
		glRasterPos2sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::RasterPos3d:
		glRasterPos3d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::RasterPos3dv:
		glRasterPos3dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::RasterPos3f:
		glRasterPos3f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::RasterPos3fv:
		glRasterPos3fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::RasterPos3i:
		glRasterPos3i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::RasterPos3iv:
		glRasterPos3iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::RasterPos3s:
		glRasterPos3s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::RasterPos3sv:
		glRasterPos3sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::RasterPos4d:
		glRasterPos4d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::RasterPos4dv:
		glRasterPos4dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::RasterPos4f:
		glRasterPos4f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::RasterPos4fv:
		glRasterPos4fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::RasterPos4i:
		glRasterPos4i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::RasterPos4iv:
		glRasterPos4iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::RasterPos4s:
		glRasterPos4s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24)); break;
	case GLFunctions::RasterPos4sv:
		glRasterPos4sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::ReadBuffer:
		glReadBuffer(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::ReadPixels:
		glReadPixels(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLenum*>(Registers+32),
			*reinterpret_cast<GLenum*>(Registers+40),
			*reinterpret_cast<GLvoid **>(Registers+48)); break;
	case GLFunctions::Rectd:
		glRectd(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::Rectdv:
		glRectdv(*reinterpret_cast<const GLdouble **>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::Rectf:
		glRectf(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::Rectfv:
		glRectfv(*reinterpret_cast<const GLfloat **>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::Recti:
		glRecti(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::Rectiv:
		glRectiv(*reinterpret_cast<const GLint **>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::Rects:
		glRects(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24)); break;
	case GLFunctions::Rectsv:
		glRectsv(*reinterpret_cast<const GLshort **>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::ReleaseShaderCompiler:
		glReleaseShaderCompiler(); break;
	case GLFunctions::RenderMode:
		glRenderMode(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::RenderbufferStorage:
		glRenderbufferStorage(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::RenderbufferStorageMultisample:
		glRenderbufferStorageMultisample(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32)); break;
	case GLFunctions::ResumeTransformFeedback:
		glResumeTransformFeedback(); break;
	case GLFunctions::Rotated:
		glRotated(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::Rotatef:
		glRotatef(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::SampleCoverage:
		glSampleCoverage(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLboolean*>(Registers+8)); break;
	case GLFunctions::SampleMaski:
		glSampleMaski(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLbitfield*>(Registers+8)); break;
	case GLFunctions::SamplerParameterIiv:
		glSamplerParameterIiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::SamplerParameterIuiv:
		glSamplerParameterIuiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::SamplerParameterf:
		glSamplerParameterf(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::SamplerParameterfv:
		glSamplerParameterfv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::SamplerParameteri:
		glSamplerParameteri(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::SamplerParameteriv:
		glSamplerParameteriv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::Scaled:
		glScaled(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::Scalef:
		glScalef(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::Scissor:
		glScissor(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::ScissorArrayv:
		glScissorArrayv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::ScissorIndexed:
		glScissorIndexed(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32)); break;
	case GLFunctions::ScissorIndexedv:
		glScissorIndexedv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::SecondaryColor3b:
		glSecondaryColor3b(*reinterpret_cast<GLbyte*>(Registers),
			*reinterpret_cast<GLbyte*>(Registers+8),
			*reinterpret_cast<GLbyte*>(Registers+16)); break;
	case GLFunctions::SecondaryColor3bv:
		glSecondaryColor3bv(*reinterpret_cast<const GLbyte **>(Registers)); break;
	case GLFunctions::SecondaryColor3d:
		glSecondaryColor3d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::SecondaryColor3dv:
		glSecondaryColor3dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::SecondaryColor3f:
		glSecondaryColor3f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::SecondaryColor3fv:
		glSecondaryColor3fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::SecondaryColor3i:
		glSecondaryColor3i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::SecondaryColor3iv:
		glSecondaryColor3iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::SecondaryColor3s:
		glSecondaryColor3s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::SecondaryColor3sv:
		glSecondaryColor3sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::SecondaryColor3ub:
		glSecondaryColor3ub(*reinterpret_cast<GLubyte*>(Registers),
			*reinterpret_cast<GLubyte*>(Registers+8),
			*reinterpret_cast<GLubyte*>(Registers+16)); break;
	case GLFunctions::SecondaryColor3ubv:
		glSecondaryColor3ubv(*reinterpret_cast<const GLubyte **>(Registers)); break;
	case GLFunctions::SecondaryColor3ui:
		glSecondaryColor3ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::SecondaryColor3uiv:
		glSecondaryColor3uiv(*reinterpret_cast<const GLuint **>(Registers)); break;
	case GLFunctions::SecondaryColor3us:
		glSecondaryColor3us(*reinterpret_cast<GLushort*>(Registers),
			*reinterpret_cast<GLushort*>(Registers+8),
			*reinterpret_cast<GLushort*>(Registers+16)); break;
	case GLFunctions::SecondaryColor3usv:
		glSecondaryColor3usv(*reinterpret_cast<const GLushort **>(Registers)); break;
	case GLFunctions::SecondaryColorP3ui:
		glSecondaryColorP3ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::SecondaryColorP3uiv:
		glSecondaryColorP3uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::SecondaryColorPointer:
		glSecondaryColorPointer(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24)); break;
	case GLFunctions::SelectBuffer:
		glSelectBuffer(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<GLuint **>(Registers+8)); break;
	case GLFunctions::ShadeModel:
		glShadeModel(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::ShaderBinary:
		glShaderBinary(*reinterpret_cast<GLsizei*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32)); break;
	case GLFunctions::ShaderSource:
		glShaderSource(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLchar *const**>(Registers+16),
			*reinterpret_cast<const GLint **>(Registers+24)); break;
	case GLFunctions::ShaderStorageBlockBinding:
		glShaderStorageBlockBinding(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::StencilFunc:
		glStencilFunc(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::StencilFuncSeparate:
		glStencilFuncSeparate(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::StencilMask:
		glStencilMask(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::StencilMaskSeparate:
		glStencilMaskSeparate(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::StencilOp:
		glStencilOp(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16)); break;
	case GLFunctions::StencilOpSeparate:
		glStencilOpSeparate(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24)); break;
	case GLFunctions::TexBuffer:
		glTexBuffer(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::TexBufferRange:
		glTexBufferRange(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLintptr*>(Registers+24),
			*reinterpret_cast<GLsizeiptr*>(Registers+32)); break;
	case GLFunctions::TexCoord1d:
		glTexCoord1d(*reinterpret_cast<GLdouble*>(Registers)); break;
	case GLFunctions::TexCoord1dv:
		glTexCoord1dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::TexCoord1f:
		glTexCoord1f(*reinterpret_cast<GLfloat*>(Registers)); break;
	case GLFunctions::TexCoord1fv:
		glTexCoord1fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::TexCoord1i:
		glTexCoord1i(*reinterpret_cast<GLint*>(Registers)); break;
	case GLFunctions::TexCoord1iv:
		glTexCoord1iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::TexCoord1s:
		glTexCoord1s(*reinterpret_cast<GLshort*>(Registers)); break;
	case GLFunctions::TexCoord1sv:
		glTexCoord1sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::TexCoord2d:
		glTexCoord2d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::TexCoord2dv:
		glTexCoord2dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::TexCoord2f:
		glTexCoord2f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::TexCoord2fv:
		glTexCoord2fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::TexCoord2i:
		glTexCoord2i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::TexCoord2iv:
		glTexCoord2iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::TexCoord2s:
		glTexCoord2s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8)); break;
	case GLFunctions::TexCoord2sv:
		glTexCoord2sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::TexCoord3d:
		glTexCoord3d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::TexCoord3dv:
		glTexCoord3dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::TexCoord3f:
		glTexCoord3f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::TexCoord3fv:
		glTexCoord3fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::TexCoord3i:
		glTexCoord3i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::TexCoord3iv:
		glTexCoord3iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::TexCoord3s:
		glTexCoord3s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::TexCoord3sv:
		glTexCoord3sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::TexCoord4d:
		glTexCoord4d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::TexCoord4dv:
		glTexCoord4dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::TexCoord4f:
		glTexCoord4f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::TexCoord4fv:
		glTexCoord4fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::TexCoord4i:
		glTexCoord4i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::TexCoord4iv:
		glTexCoord4iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::TexCoord4s:
		glTexCoord4s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24)); break;
	case GLFunctions::TexCoord4sv:
		glTexCoord4sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::TexCoordP1ui:
		glTexCoordP1ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::TexCoordP1uiv:
		glTexCoordP1uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::TexCoordP2ui:
		glTexCoordP2ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::TexCoordP2uiv:
		glTexCoordP2uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::TexCoordP3ui:
		glTexCoordP3ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::TexCoordP3uiv:
		glTexCoordP3uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::TexCoordP4ui:
		glTexCoordP4ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::TexCoordP4uiv:
		glTexCoordP4uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::TexCoordPointer:
		glTexCoordPointer(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24)); break;
	case GLFunctions::TexEnvf:
		glTexEnvf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::TexEnvfv:
		glTexEnvfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::TexEnvi:
		glTexEnvi(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::TexEnviv:
		glTexEnviv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::TexGend:
		glTexGend(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::TexGendv:
		glTexGendv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLdouble **>(Registers+16)); break;
	case GLFunctions::TexGenf:
		glTexGenf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::TexGenfv:
		glTexGenfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::TexGeni:
		glTexGeni(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::TexGeniv:
		glTexGeniv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::TexImage1D:
		glTexImage1D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLenum*>(Registers+40),
			*reinterpret_cast<GLenum*>(Registers+48),
			*reinterpret_cast<const GLvoid **>(Registers+56)); break;
	case GLFunctions::TexImage2D:
		glTexImage2D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLint*>(Registers+40),
			*reinterpret_cast<GLenum*>(Registers+48),
			*reinterpret_cast<GLenum*>(Registers+56),
			*reinterpret_cast<const GLvoid **>(Registers+64)); break;
	case GLFunctions::TexImage2DMultisample:
		glTexImage2DMultisample(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLboolean*>(Registers+40)); break;
	case GLFunctions::TexImage3D:
		glTexImage3D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLint*>(Registers+48),
			*reinterpret_cast<GLenum*>(Registers+56),
			*reinterpret_cast<GLenum*>(Registers+64),
			*reinterpret_cast<const GLvoid **>(Registers+72)); break;
	case GLFunctions::TexImage3DMultisample:
		glTexImage3DMultisample(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLboolean*>(Registers+48)); break;
	case GLFunctions::TexParameterIiv:
		glTexParameterIiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::TexParameterIuiv:
		glTexParameterIuiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::TexParameterf:
		glTexParameterf(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::TexParameterfv:
		glTexParameterfv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::TexParameteri:
		glTexParameteri(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::TexParameteriv:
		glTexParameteriv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::TexStorage1D:
		glTexStorage1D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::TexStorage2D:
		glTexStorage2D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32)); break;
	case GLFunctions::TexStorage2DMultisample:
		glTexStorage2DMultisample(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLboolean*>(Registers+40)); break;
	case GLFunctions::TexStorage3D:
		glTexStorage3D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40)); break;
	case GLFunctions::TexStorage3DMultisample:
		glTexStorage3DMultisample(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLboolean*>(Registers+48)); break;
	case GLFunctions::TexSubImage1D:
		glTexSubImage1D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<GLenum*>(Registers+32),
			*reinterpret_cast<GLenum*>(Registers+40),
			*reinterpret_cast<const GLvoid **>(Registers+48)); break;
	case GLFunctions::TexSubImage2D:
		glTexSubImage2D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLenum*>(Registers+48),
			*reinterpret_cast<GLenum*>(Registers+56),
			*reinterpret_cast<const GLvoid **>(Registers+64)); break;
	case GLFunctions::TexSubImage3D:
		glTexSubImage3D(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32),
			*reinterpret_cast<GLsizei*>(Registers+40),
			*reinterpret_cast<GLsizei*>(Registers+48),
			*reinterpret_cast<GLsizei*>(Registers+56),
			*reinterpret_cast<GLenum*>(Registers+64),
			*reinterpret_cast<GLenum*>(Registers+72),
			*reinterpret_cast<const GLvoid **>(Registers+80)); break;
	case GLFunctions::TextureView:
		glTextureView(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24),
			*reinterpret_cast<GLuint*>(Registers+32),
			*reinterpret_cast<GLuint*>(Registers+40),
			*reinterpret_cast<GLuint*>(Registers+48),
			*reinterpret_cast<GLuint*>(Registers+56)); break;
	case GLFunctions::TransformFeedbackVaryings:
		glTransformFeedbackVaryings(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLchar *const**>(Registers+16),
			*reinterpret_cast<GLenum*>(Registers+24)); break;
	case GLFunctions::Translated:
		glTranslated(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::Translatef:
		glTranslatef(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::Uniform1d:
		glUniform1d(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::Uniform1dv:
		glUniform1dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLdouble **>(Registers+16)); break;
	case GLFunctions::Uniform1f:
		glUniform1f(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::Uniform1fv:
		glUniform1fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::Uniform1i:
		glUniform1i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::Uniform1iv:
		glUniform1iv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::Uniform1ui:
		glUniform1ui(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::Uniform1uiv:
		glUniform1uiv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::Uniform2d:
		glUniform2d(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::Uniform2dv:
		glUniform2dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLdouble **>(Registers+16)); break;
	case GLFunctions::Uniform2f:
		glUniform2f(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::Uniform2fv:
		glUniform2fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::Uniform2i:
		glUniform2i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::Uniform2iv:
		glUniform2iv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::Uniform2ui:
		glUniform2ui(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::Uniform2uiv:
		glUniform2uiv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::Uniform3d:
		glUniform3d(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::Uniform3dv:
		glUniform3dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLdouble **>(Registers+16)); break;
	case GLFunctions::Uniform3f:
		glUniform3f(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::Uniform3fv:
		glUniform3fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::Uniform3i:
		glUniform3i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::Uniform3iv:
		glUniform3iv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::Uniform3ui:
		glUniform3ui(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::Uniform3uiv:
		glUniform3uiv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::Uniform4d:
		glUniform4d(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32)); break;
	case GLFunctions::Uniform4dv:
		glUniform4dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLdouble **>(Registers+16)); break;
	case GLFunctions::Uniform4f:
		glUniform4f(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24),
			*reinterpret_cast<GLfloat*>(Registers+32)); break;
	case GLFunctions::Uniform4fv:
		glUniform4fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::Uniform4i:
		glUniform4i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::Uniform4iv:
		glUniform4iv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLint **>(Registers+16)); break;
	case GLFunctions::Uniform4ui:
		glUniform4ui(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24),
			*reinterpret_cast<GLuint*>(Registers+32)); break;
	case GLFunctions::Uniform4uiv:
		glUniform4uiv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::UniformBlockBinding:
		glUniformBlockBinding(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::UniformMatrix2dv:
		glUniformMatrix2dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix2fv:
		glUniformMatrix2fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformMatrix2x3dv:
		glUniformMatrix2x3dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix2x3fv:
		glUniformMatrix2x3fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformMatrix2x4dv:
		glUniformMatrix2x4dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix2x4fv:
		glUniformMatrix2x4fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformMatrix3dv:
		glUniformMatrix3dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix3fv:
		glUniformMatrix3fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformMatrix3x2dv:
		glUniformMatrix3x2dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix3x2fv:
		glUniformMatrix3x2fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformMatrix3x4dv:
		glUniformMatrix3x4dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix3x4fv:
		glUniformMatrix3x4fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformMatrix4dv:
		glUniformMatrix4dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix4fv:
		glUniformMatrix4fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformMatrix4x2dv:
		glUniformMatrix4x2dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix4x2fv:
		glUniformMatrix4x2fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformMatrix4x3dv:
		glUniformMatrix4x3dv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLdouble **>(Registers+24)); break;
	case GLFunctions::UniformMatrix4x3fv:
		glUniformMatrix4x3fv(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLfloat **>(Registers+24)); break;
	case GLFunctions::UniformSubroutinesuiv:
		glUniformSubroutinesuiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLuint **>(Registers+16)); break;
	case GLFunctions::UnmapBuffer:
		glUnmapBuffer(*reinterpret_cast<GLenum*>(Registers)); break;
	case GLFunctions::UseProgram:
		glUseProgram(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::UseProgramStages:
		glUseProgramStages(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLbitfield*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::ValidateProgram:
		glValidateProgram(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::ValidateProgramPipeline:
		glValidateProgramPipeline(*reinterpret_cast<GLuint*>(Registers)); break;
	case GLFunctions::Vertex2d:
		glVertex2d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::Vertex2dv:
		glVertex2dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::Vertex2f:
		glVertex2f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::Vertex2fv:
		glVertex2fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::Vertex2i:
		glVertex2i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::Vertex2iv:
		glVertex2iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::Vertex2s:
		glVertex2s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8)); break;
	case GLFunctions::Vertex2sv:
		glVertex2sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::Vertex3d:
		glVertex3d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::Vertex3dv:
		glVertex3dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::Vertex3f:
		glVertex3f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::Vertex3fv:
		glVertex3fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::Vertex3i:
		glVertex3i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::Vertex3iv:
		glVertex3iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::Vertex3s:
		glVertex3s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::Vertex3sv:
		glVertex3sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::Vertex4d:
		glVertex4d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::Vertex4dv:
		glVertex4dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::Vertex4f:
		glVertex4f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::Vertex4fv:
		glVertex4fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::Vertex4i:
		glVertex4i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::Vertex4iv:
		glVertex4iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::Vertex4s:
		glVertex4s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24)); break;
	case GLFunctions::Vertex4sv:
		glVertex4sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::VertexAttrib1d:
		glVertexAttrib1d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::VertexAttrib1dv:
		glVertexAttrib1dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::VertexAttrib1f:
		glVertexAttrib1f(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::VertexAttrib1fv:
		glVertexAttrib1fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::VertexAttrib1s:
		glVertexAttrib1s(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8)); break;
	case GLFunctions::VertexAttrib1sv:
		glVertexAttrib1sv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::VertexAttrib2d:
		glVertexAttrib2d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::VertexAttrib2dv:
		glVertexAttrib2dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::VertexAttrib2f:
		glVertexAttrib2f(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::VertexAttrib2fv:
		glVertexAttrib2fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::VertexAttrib2s:
		glVertexAttrib2s(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::VertexAttrib2sv:
		glVertexAttrib2sv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::VertexAttrib3d:
		glVertexAttrib3d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::VertexAttrib3dv:
		glVertexAttrib3dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::VertexAttrib3f:
		glVertexAttrib3f(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24)); break;
	case GLFunctions::VertexAttrib3fv:
		glVertexAttrib3fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::VertexAttrib3s:
		glVertexAttrib3s(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24)); break;
	case GLFunctions::VertexAttrib3sv:
		glVertexAttrib3sv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4Nbv:
		glVertexAttrib4Nbv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLbyte **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4Niv:
		glVertexAttrib4Niv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4Nsv:
		glVertexAttrib4Nsv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4Nub:
		glVertexAttrib4Nub(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLubyte*>(Registers+8),
			*reinterpret_cast<GLubyte*>(Registers+16),
			*reinterpret_cast<GLubyte*>(Registers+24),
			*reinterpret_cast<GLubyte*>(Registers+32)); break;
	case GLFunctions::VertexAttrib4Nubv:
		glVertexAttrib4Nubv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLubyte **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4Nuiv:
		glVertexAttrib4Nuiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4Nusv:
		glVertexAttrib4Nusv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLushort **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4bv:
		glVertexAttrib4bv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLbyte **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4d:
		glVertexAttrib4d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32)); break;
	case GLFunctions::VertexAttrib4dv:
		glVertexAttrib4dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4f:
		glVertexAttrib4f(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24),
			*reinterpret_cast<GLfloat*>(Registers+32)); break;
	case GLFunctions::VertexAttrib4fv:
		glVertexAttrib4fv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4iv:
		glVertexAttrib4iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4s:
		glVertexAttrib4s(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16),
			*reinterpret_cast<GLshort*>(Registers+24),
			*reinterpret_cast<GLshort*>(Registers+32)); break;
	case GLFunctions::VertexAttrib4sv:
		glVertexAttrib4sv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4ubv:
		glVertexAttrib4ubv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLubyte **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4uiv:
		glVertexAttrib4uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexAttrib4usv:
		glVertexAttrib4usv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLushort **>(Registers+8)); break;
	case GLFunctions::VertexAttribBinding:
		glVertexAttribBinding(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::VertexAttribDivisor:
		glVertexAttribDivisor(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::VertexAttribFormat:
		glVertexAttribFormat(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<GLuint*>(Registers+32)); break;
	case GLFunctions::VertexAttribI1i:
		glVertexAttribI1i(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::VertexAttribI1iv:
		glVertexAttribI1iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::VertexAttribI1ui:
		glVertexAttribI1ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::VertexAttribI1uiv:
		glVertexAttribI1uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexAttribI2i:
		glVertexAttribI2i(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::VertexAttribI2iv:
		glVertexAttribI2iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::VertexAttribI2ui:
		glVertexAttribI2ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16)); break;
	case GLFunctions::VertexAttribI2uiv:
		glVertexAttribI2uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexAttribI3i:
		glVertexAttribI3i(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24)); break;
	case GLFunctions::VertexAttribI3iv:
		glVertexAttribI3iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::VertexAttribI3ui:
		glVertexAttribI3ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::VertexAttribI3uiv:
		glVertexAttribI3uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexAttribI4bv:
		glVertexAttribI4bv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLbyte **>(Registers+8)); break;
	case GLFunctions::VertexAttribI4i:
		glVertexAttribI4i(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16),
			*reinterpret_cast<GLint*>(Registers+24),
			*reinterpret_cast<GLint*>(Registers+32)); break;
	case GLFunctions::VertexAttribI4iv:
		glVertexAttribI4iv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLint **>(Registers+8)); break;
	case GLFunctions::VertexAttribI4sv:
		glVertexAttribI4sv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLshort **>(Registers+8)); break;
	case GLFunctions::VertexAttribI4ubv:
		glVertexAttribI4ubv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLubyte **>(Registers+8)); break;
	case GLFunctions::VertexAttribI4ui:
		glVertexAttribI4ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8),
			*reinterpret_cast<GLuint*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24),
			*reinterpret_cast<GLuint*>(Registers+32)); break;
	case GLFunctions::VertexAttribI4uiv:
		glVertexAttribI4uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexAttribI4usv:
		glVertexAttribI4usv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLushort **>(Registers+8)); break;
	case GLFunctions::VertexAttribIFormat:
		glVertexAttribIFormat(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::VertexAttribIPointer:
		glVertexAttribIPointer(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<const GLvoid **>(Registers+32)); break;
	case GLFunctions::VertexAttribL1d:
		glVertexAttribL1d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::VertexAttribL1dv:
		glVertexAttribL1dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::VertexAttribL2d:
		glVertexAttribL2d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::VertexAttribL2dv:
		glVertexAttribL2dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::VertexAttribL3d:
		glVertexAttribL3d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24)); break;
	case GLFunctions::VertexAttribL3dv:
		glVertexAttribL3dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::VertexAttribL4d:
		glVertexAttribL4d(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16),
			*reinterpret_cast<GLdouble*>(Registers+24),
			*reinterpret_cast<GLdouble*>(Registers+32)); break;
	case GLFunctions::VertexAttribL4dv:
		glVertexAttribL4dv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLdouble **>(Registers+8)); break;
	case GLFunctions::VertexAttribLFormat:
		glVertexAttribLFormat(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::VertexAttribLPointer:
		glVertexAttribLPointer(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24),
			*reinterpret_cast<const GLvoid **>(Registers+32)); break;
	case GLFunctions::VertexAttribP1ui:
		glVertexAttribP1ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::VertexAttribP1uiv:
		glVertexAttribP1uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::VertexAttribP2ui:
		glVertexAttribP2ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::VertexAttribP2uiv:
		glVertexAttribP2uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::VertexAttribP3ui:
		glVertexAttribP3ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::VertexAttribP3uiv:
		glVertexAttribP3uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::VertexAttribP4ui:
		glVertexAttribP4ui(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<GLuint*>(Registers+24)); break;
	case GLFunctions::VertexAttribP4uiv:
		glVertexAttribP4uiv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLboolean*>(Registers+16),
			*reinterpret_cast<const GLuint **>(Registers+24)); break;
	case GLFunctions::VertexAttribPointer:
		glVertexAttribPointer(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLenum*>(Registers+16),
			*reinterpret_cast<GLboolean*>(Registers+24),
			*reinterpret_cast<GLsizei*>(Registers+32),
			*reinterpret_cast<const GLvoid **>(Registers+40)); break;
	case GLFunctions::VertexBindingDivisor:
		glVertexBindingDivisor(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::VertexP2ui:
		glVertexP2ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::VertexP2uiv:
		glVertexP2uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexP3ui:
		glVertexP3ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::VertexP3uiv:
		glVertexP3uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexP4ui:
		glVertexP4ui(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<GLuint*>(Registers+8)); break;
	case GLFunctions::VertexP4uiv:
		glVertexP4uiv(*reinterpret_cast<GLenum*>(Registers),
			*reinterpret_cast<const GLuint **>(Registers+8)); break;
	case GLFunctions::VertexPointer:
		glVertexPointer(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLenum*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<const GLvoid **>(Registers+24)); break;
	case GLFunctions::Viewport:
		glViewport(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLsizei*>(Registers+16),
			*reinterpret_cast<GLsizei*>(Registers+24)); break;
	case GLFunctions::ViewportArrayv:
		glViewportArrayv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLsizei*>(Registers+8),
			*reinterpret_cast<const GLfloat **>(Registers+16)); break;
	case GLFunctions::ViewportIndexedf:
		glViewportIndexedf(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16),
			*reinterpret_cast<GLfloat*>(Registers+24),
			*reinterpret_cast<GLfloat*>(Registers+32)); break;
	case GLFunctions::ViewportIndexedfv:
		glViewportIndexedfv(*reinterpret_cast<GLuint*>(Registers),
			*reinterpret_cast<const GLfloat **>(Registers+8)); break;
	case GLFunctions::WaitSync:
		glWaitSync(*reinterpret_cast<GLsync*>(Registers),
			*reinterpret_cast<GLbitfield*>(Registers+8),
			*reinterpret_cast<GLuint64*>(Registers+16)); break;
	case GLFunctions::WindowPos2d:
		glWindowPos2d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8)); break;
	case GLFunctions::WindowPos2dv:
		glWindowPos2dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::WindowPos2f:
		glWindowPos2f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8)); break;
	case GLFunctions::WindowPos2fv:
		glWindowPos2fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::WindowPos2i:
		glWindowPos2i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8)); break;
	case GLFunctions::WindowPos2iv:
		glWindowPos2iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::WindowPos2s:
		glWindowPos2s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8)); break;
	case GLFunctions::WindowPos2sv:
		glWindowPos2sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	case GLFunctions::WindowPos3d:
		glWindowPos3d(*reinterpret_cast<GLdouble*>(Registers),
			*reinterpret_cast<GLdouble*>(Registers+8),
			*reinterpret_cast<GLdouble*>(Registers+16)); break;
	case GLFunctions::WindowPos3dv:
		glWindowPos3dv(*reinterpret_cast<const GLdouble **>(Registers)); break;
	case GLFunctions::WindowPos3f:
		glWindowPos3f(*reinterpret_cast<GLfloat*>(Registers),
			*reinterpret_cast<GLfloat*>(Registers+8),
			*reinterpret_cast<GLfloat*>(Registers+16)); break;
	case GLFunctions::WindowPos3fv:
		glWindowPos3fv(*reinterpret_cast<const GLfloat **>(Registers)); break;
	case GLFunctions::WindowPos3i:
		glWindowPos3i(*reinterpret_cast<GLint*>(Registers),
			*reinterpret_cast<GLint*>(Registers+8),
			*reinterpret_cast<GLint*>(Registers+16)); break;
	case GLFunctions::WindowPos3iv:
		glWindowPos3iv(*reinterpret_cast<const GLint **>(Registers)); break;
	case GLFunctions::WindowPos3s:
		glWindowPos3s(*reinterpret_cast<GLshort*>(Registers),
			*reinterpret_cast<GLshort*>(Registers+8),
			*reinterpret_cast<GLshort*>(Registers+16)); break;
	case GLFunctions::WindowPos3sv:
		glWindowPos3sv(*reinterpret_cast<const GLshort **>(Registers)); break;
	}
}

void OpenGLMachine::CallOpCode(GLOpCode::Type ID, UInt8*& Data)
{
	switch(ID)
	{
	case GLOpCode::MoveFloat32Reg0: *reinterpret_cast<Float32*>(Registers+0)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg0: *reinterpret_cast<Float64*>(Registers+0)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg0: *reinterpret_cast<Int16*>(Registers+0)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg0: *reinterpret_cast<Int32*>(Registers+0)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg0: *reinterpret_cast<Int64*>(Registers+0)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg0: *reinterpret_cast<UInt16*>(Registers+0)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg0: *reinterpret_cast<UInt32*>(Registers+0)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg0: *reinterpret_cast<UInt64*>(Registers+0)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg0: *reinterpret_cast<void**>(Registers+0)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg1: *reinterpret_cast<Float32*>(Registers+8)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg1: *reinterpret_cast<Float64*>(Registers+8)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg1: *reinterpret_cast<Int16*>(Registers+8)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg1: *reinterpret_cast<Int32*>(Registers+8)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg1: *reinterpret_cast<Int64*>(Registers+8)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg1: *reinterpret_cast<UInt16*>(Registers+8)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg1: *reinterpret_cast<UInt32*>(Registers+8)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg1: *reinterpret_cast<UInt64*>(Registers+8)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg1: *reinterpret_cast<void**>(Registers+8)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg2: *reinterpret_cast<Float32*>(Registers+16)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg2: *reinterpret_cast<Float64*>(Registers+16)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg2: *reinterpret_cast<Int16*>(Registers+16)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg2: *reinterpret_cast<Int32*>(Registers+16)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg2: *reinterpret_cast<Int64*>(Registers+16)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg2: *reinterpret_cast<UInt16*>(Registers+16)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg2: *reinterpret_cast<UInt32*>(Registers+16)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg2: *reinterpret_cast<UInt64*>(Registers+16)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg2: *reinterpret_cast<void**>(Registers+16)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg3: *reinterpret_cast<Float32*>(Registers+24)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg3: *reinterpret_cast<Float64*>(Registers+24)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg3: *reinterpret_cast<Int16*>(Registers+24)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg3: *reinterpret_cast<Int32*>(Registers+24)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg3: *reinterpret_cast<Int64*>(Registers+24)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg3: *reinterpret_cast<UInt16*>(Registers+24)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg3: *reinterpret_cast<UInt32*>(Registers+24)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg3: *reinterpret_cast<UInt64*>(Registers+24)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg3: *reinterpret_cast<void**>(Registers+24)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg4: *reinterpret_cast<Float32*>(Registers+32)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg4: *reinterpret_cast<Float64*>(Registers+32)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg4: *reinterpret_cast<Int16*>(Registers+32)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg4: *reinterpret_cast<Int32*>(Registers+32)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg4: *reinterpret_cast<Int64*>(Registers+32)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg4: *reinterpret_cast<UInt16*>(Registers+32)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg4: *reinterpret_cast<UInt32*>(Registers+32)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg4: *reinterpret_cast<UInt64*>(Registers+32)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg4: *reinterpret_cast<void**>(Registers+32)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg5: *reinterpret_cast<Float32*>(Registers+40)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg5: *reinterpret_cast<Float64*>(Registers+40)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg5: *reinterpret_cast<Int16*>(Registers+40)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg5: *reinterpret_cast<Int32*>(Registers+40)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg5: *reinterpret_cast<Int64*>(Registers+40)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg5: *reinterpret_cast<UInt16*>(Registers+40)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg5: *reinterpret_cast<UInt32*>(Registers+40)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg5: *reinterpret_cast<UInt64*>(Registers+40)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg5: *reinterpret_cast<void**>(Registers+40)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg6: *reinterpret_cast<Float32*>(Registers+48)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg6: *reinterpret_cast<Float64*>(Registers+48)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg6: *reinterpret_cast<Int16*>(Registers+48)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg6: *reinterpret_cast<Int32*>(Registers+48)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg6: *reinterpret_cast<Int64*>(Registers+48)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg6: *reinterpret_cast<UInt16*>(Registers+48)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg6: *reinterpret_cast<UInt32*>(Registers+48)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg6: *reinterpret_cast<UInt64*>(Registers+48)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg6: *reinterpret_cast<void**>(Registers+48)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg7: *reinterpret_cast<Float32*>(Registers+56)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg7: *reinterpret_cast<Float64*>(Registers+56)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg7: *reinterpret_cast<Int16*>(Registers+56)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg7: *reinterpret_cast<Int32*>(Registers+56)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg7: *reinterpret_cast<Int64*>(Registers+56)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg7: *reinterpret_cast<UInt16*>(Registers+56)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg7: *reinterpret_cast<UInt32*>(Registers+56)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg7: *reinterpret_cast<UInt64*>(Registers+56)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg7: *reinterpret_cast<void**>(Registers+56)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg8: *reinterpret_cast<Float32*>(Registers+64)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg8: *reinterpret_cast<Float64*>(Registers+64)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg8: *reinterpret_cast<Int16*>(Registers+64)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg8: *reinterpret_cast<Int32*>(Registers+64)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg8: *reinterpret_cast<Int64*>(Registers+64)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg8: *reinterpret_cast<UInt16*>(Registers+64)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg8: *reinterpret_cast<UInt32*>(Registers+64)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg8: *reinterpret_cast<UInt64*>(Registers+64)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg8: *reinterpret_cast<void**>(Registers+64)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg9: *reinterpret_cast<Float32*>(Registers+72)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg9: *reinterpret_cast<Float64*>(Registers+72)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg9: *reinterpret_cast<Int16*>(Registers+72)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg9: *reinterpret_cast<Int32*>(Registers+72)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg9: *reinterpret_cast<Int64*>(Registers+72)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg9: *reinterpret_cast<UInt16*>(Registers+72)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg9: *reinterpret_cast<UInt32*>(Registers+72)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg9: *reinterpret_cast<UInt64*>(Registers+72)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg9: *reinterpret_cast<void**>(Registers+72)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg10: *reinterpret_cast<Float32*>(Registers+80)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg10: *reinterpret_cast<Float64*>(Registers+80)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg10: *reinterpret_cast<Int16*>(Registers+80)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg10: *reinterpret_cast<Int32*>(Registers+80)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg10: *reinterpret_cast<Int64*>(Registers+80)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg10: *reinterpret_cast<UInt16*>(Registers+80)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg10: *reinterpret_cast<UInt32*>(Registers+80)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg10: *reinterpret_cast<UInt64*>(Registers+80)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg10: *reinterpret_cast<void**>(Registers+80)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg11: *reinterpret_cast<Float32*>(Registers+88)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg11: *reinterpret_cast<Float64*>(Registers+88)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg11: *reinterpret_cast<Int16*>(Registers+88)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg11: *reinterpret_cast<Int32*>(Registers+88)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg11: *reinterpret_cast<Int64*>(Registers+88)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg11: *reinterpret_cast<UInt16*>(Registers+88)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg11: *reinterpret_cast<UInt32*>(Registers+88)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg11: *reinterpret_cast<UInt64*>(Registers+88)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg11: *reinterpret_cast<void**>(Registers+88)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg12: *reinterpret_cast<Float32*>(Registers+96)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg12: *reinterpret_cast<Float64*>(Registers+96)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg12: *reinterpret_cast<Int16*>(Registers+96)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg12: *reinterpret_cast<Int32*>(Registers+96)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg12: *reinterpret_cast<Int64*>(Registers+96)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg12: *reinterpret_cast<UInt16*>(Registers+96)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg12: *reinterpret_cast<UInt32*>(Registers+96)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg12: *reinterpret_cast<UInt64*>(Registers+96)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg12: *reinterpret_cast<void**>(Registers+96)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg13: *reinterpret_cast<Float32*>(Registers+104)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg13: *reinterpret_cast<Float64*>(Registers+104)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg13: *reinterpret_cast<Int16*>(Registers+104)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg13: *reinterpret_cast<Int32*>(Registers+104)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg13: *reinterpret_cast<Int64*>(Registers+104)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg13: *reinterpret_cast<UInt16*>(Registers+104)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg13: *reinterpret_cast<UInt32*>(Registers+104)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg13: *reinterpret_cast<UInt64*>(Registers+104)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg13: *reinterpret_cast<void**>(Registers+104)=*reinterpret_cast<void**>(Data); Data+=8; break;
	case GLOpCode::MoveFloat32Reg14: *reinterpret_cast<Float32*>(Registers+112)=*reinterpret_cast<Float32*>(Data); Data+=4; break;
	case GLOpCode::MoveFloat64Reg14: *reinterpret_cast<Float64*>(Registers+112)=*reinterpret_cast<Float64*>(Data); Data+=8; break;
	case GLOpCode::MoveInt16Reg14: *reinterpret_cast<Int16*>(Registers+112)=*reinterpret_cast<Int16*>(Data); Data+=2; break;
	case GLOpCode::MoveInt32Reg14: *reinterpret_cast<Int32*>(Registers+112)=*reinterpret_cast<Int32*>(Data); Data+=4; break;
	case GLOpCode::MoveInt64Reg14: *reinterpret_cast<Int64*>(Registers+112)=*reinterpret_cast<Int64*>(Data); Data+=8; break;
	case GLOpCode::MoveUInt16Reg14: *reinterpret_cast<UInt16*>(Registers+112)=*reinterpret_cast<UInt16*>(Data); Data+=2; break;
	case GLOpCode::MoveUInt32Reg14: *reinterpret_cast<UInt32*>(Registers+112)=*reinterpret_cast<UInt32*>(Data); Data+=4; break;
	case GLOpCode::MoveUInt64Reg14: *reinterpret_cast<UInt64*>(Registers+112)=*reinterpret_cast<UInt64*>(Data); Data+=8; break;
	case GLOpCode::MovePtrReg14: *reinterpret_cast<void**>(Registers+112)=*reinterpret_cast<void**>(Data); Data+=8; break;
	}
}