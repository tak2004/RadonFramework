#include "OpenGL.hpp"
#include "OpenGLSystem.hpp"

void glAccumDispatcher(GLenum op,GLfloat value){
	glAccum = reinterpret_cast<glAccumCallback>(OpenGLGetProcAddress("glAccum"));
	glAccum(op,value);
}
glAccumCallback glAccum = glAccumDispatcher;

void glActiveShaderProgramDispatcher(GLuint pipeline,GLuint program){
	glActiveShaderProgram = reinterpret_cast<glActiveShaderProgramCallback>(OpenGLGetProcAddress("glActiveShaderProgram"));
	glActiveShaderProgram(pipeline,program);
}
glActiveShaderProgramCallback glActiveShaderProgram = glActiveShaderProgramDispatcher;

void glActiveTextureDispatcher(GLenum texture){
	glActiveTexture = reinterpret_cast<glActiveTextureCallback>(OpenGLGetProcAddress("glActiveTexture"));
	glActiveTexture(texture);
}
glActiveTextureCallback glActiveTexture = glActiveTextureDispatcher;

void glAlphaFuncDispatcher(GLenum func,GLfloat ref){
	glAlphaFunc = reinterpret_cast<glAlphaFuncCallback>(OpenGLGetProcAddress("glAlphaFunc"));
	glAlphaFunc(func,ref);
}
glAlphaFuncCallback glAlphaFunc = glAlphaFuncDispatcher;

GLboolean glAreTexturesResidentDispatcher(GLsizei n,const GLuint * textures,GLboolean * residences){
	glAreTexturesResident = reinterpret_cast<glAreTexturesResidentCallback>(OpenGLGetProcAddress("glAreTexturesResident"));
	return 	glAreTexturesResident(n,textures,residences);
}
glAreTexturesResidentCallback glAreTexturesResident = glAreTexturesResidentDispatcher;

void glArrayElementDispatcher(GLint i){
	glArrayElement = reinterpret_cast<glArrayElementCallback>(OpenGLGetProcAddress("glArrayElement"));
	glArrayElement(i);
}
glArrayElementCallback glArrayElement = glArrayElementDispatcher;

void glAttachShaderDispatcher(GLuint program,GLuint shader){
	glAttachShader = reinterpret_cast<glAttachShaderCallback>(OpenGLGetProcAddress("glAttachShader"));
	glAttachShader(program,shader);
}
glAttachShaderCallback glAttachShader = glAttachShaderDispatcher;

void glBeginDispatcher(GLenum mode){
	glBegin = reinterpret_cast<glBeginCallback>(OpenGLGetProcAddress("glBegin"));
	glBegin(mode);
}
glBeginCallback glBegin = glBeginDispatcher;

void glBeginConditionalRenderDispatcher(GLuint id,GLenum mode){
	glBeginConditionalRender = reinterpret_cast<glBeginConditionalRenderCallback>(OpenGLGetProcAddress("glBeginConditionalRender"));
	glBeginConditionalRender(id,mode);
}
glBeginConditionalRenderCallback glBeginConditionalRender = glBeginConditionalRenderDispatcher;

void glBeginQueryDispatcher(GLenum target,GLuint id){
	glBeginQuery = reinterpret_cast<glBeginQueryCallback>(OpenGLGetProcAddress("glBeginQuery"));
	glBeginQuery(target,id);
}
glBeginQueryCallback glBeginQuery = glBeginQueryDispatcher;

void glBeginQueryIndexedDispatcher(GLenum target,GLuint index,GLuint id){
	glBeginQueryIndexed = reinterpret_cast<glBeginQueryIndexedCallback>(OpenGLGetProcAddress("glBeginQueryIndexed"));
	glBeginQueryIndexed(target,index,id);
}
glBeginQueryIndexedCallback glBeginQueryIndexed = glBeginQueryIndexedDispatcher;

void glBeginTransformFeedbackDispatcher(GLenum primitiveMode){
	glBeginTransformFeedback = reinterpret_cast<glBeginTransformFeedbackCallback>(OpenGLGetProcAddress("glBeginTransformFeedback"));
	glBeginTransformFeedback(primitiveMode);
}
glBeginTransformFeedbackCallback glBeginTransformFeedback = glBeginTransformFeedbackDispatcher;

void glBindAttribLocationDispatcher(GLuint program,GLuint index,const GLchar * name){
	glBindAttribLocation = reinterpret_cast<glBindAttribLocationCallback>(OpenGLGetProcAddress("glBindAttribLocation"));
	glBindAttribLocation(program,index,name);
}
glBindAttribLocationCallback glBindAttribLocation = glBindAttribLocationDispatcher;

void glBindBufferDispatcher(GLenum target,GLuint buffer){
	glBindBuffer = reinterpret_cast<glBindBufferCallback>(OpenGLGetProcAddress("glBindBuffer"));
	glBindBuffer(target,buffer);
}
glBindBufferCallback glBindBuffer = glBindBufferDispatcher;

void glBindBufferBaseDispatcher(GLenum target,GLuint index,GLuint buffer){
	glBindBufferBase = reinterpret_cast<glBindBufferBaseCallback>(OpenGLGetProcAddress("glBindBufferBase"));
	glBindBufferBase(target,index,buffer);
}
glBindBufferBaseCallback glBindBufferBase = glBindBufferBaseDispatcher;

void glBindBufferRangeDispatcher(GLenum target,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size){
	glBindBufferRange = reinterpret_cast<glBindBufferRangeCallback>(OpenGLGetProcAddress("glBindBufferRange"));
	glBindBufferRange(target,index,buffer,offset,size);
}
glBindBufferRangeCallback glBindBufferRange = glBindBufferRangeDispatcher;

void glBindBuffersBaseDispatcher(GLenum target,GLuint first,GLsizei count,const GLuint * buffers){
	glBindBuffersBase = reinterpret_cast<glBindBuffersBaseCallback>(OpenGLGetProcAddress("glBindBuffersBase"));
	glBindBuffersBase(target,first,count,buffers);
}
glBindBuffersBaseCallback glBindBuffersBase = glBindBuffersBaseDispatcher;

void glBindBuffersRangeDispatcher(GLenum target,GLuint first,GLsizei count,const GLuint * buffers,const GLintptr * offsets,const GLsizeiptr * sizes){
	glBindBuffersRange = reinterpret_cast<glBindBuffersRangeCallback>(OpenGLGetProcAddress("glBindBuffersRange"));
	glBindBuffersRange(target,first,count,buffers,offsets,sizes);
}
glBindBuffersRangeCallback glBindBuffersRange = glBindBuffersRangeDispatcher;

void glBindFragDataLocationDispatcher(GLuint program,GLuint color,const GLchar * name){
	glBindFragDataLocation = reinterpret_cast<glBindFragDataLocationCallback>(OpenGLGetProcAddress("glBindFragDataLocation"));
	glBindFragDataLocation(program,color,name);
}
glBindFragDataLocationCallback glBindFragDataLocation = glBindFragDataLocationDispatcher;

void glBindFragDataLocationIndexedDispatcher(GLuint program,GLuint colorNumber,GLuint index,const GLchar * name){
	glBindFragDataLocationIndexed = reinterpret_cast<glBindFragDataLocationIndexedCallback>(OpenGLGetProcAddress("glBindFragDataLocationIndexed"));
	glBindFragDataLocationIndexed(program,colorNumber,index,name);
}
glBindFragDataLocationIndexedCallback glBindFragDataLocationIndexed = glBindFragDataLocationIndexedDispatcher;

void glBindFramebufferDispatcher(GLenum target,GLuint framebuffer){
	glBindFramebuffer = reinterpret_cast<glBindFramebufferCallback>(OpenGLGetProcAddress("glBindFramebuffer"));
	glBindFramebuffer(target,framebuffer);
}
glBindFramebufferCallback glBindFramebuffer = glBindFramebufferDispatcher;

void glBindImageTextureDispatcher(GLuint unit,GLuint texture,GLint level,GLboolean layered,GLint layer,GLenum access,GLenum format){
	glBindImageTexture = reinterpret_cast<glBindImageTextureCallback>(OpenGLGetProcAddress("glBindImageTexture"));
	glBindImageTexture(unit,texture,level,layered,layer,access,format);
}
glBindImageTextureCallback glBindImageTexture = glBindImageTextureDispatcher;

void glBindImageTexturesDispatcher(GLuint first,GLsizei count,const GLuint * textures){
	glBindImageTextures = reinterpret_cast<glBindImageTexturesCallback>(OpenGLGetProcAddress("glBindImageTextures"));
	glBindImageTextures(first,count,textures);
}
glBindImageTexturesCallback glBindImageTextures = glBindImageTexturesDispatcher;

void glBindProgramPipelineDispatcher(GLuint pipeline){
	glBindProgramPipeline = reinterpret_cast<glBindProgramPipelineCallback>(OpenGLGetProcAddress("glBindProgramPipeline"));
	glBindProgramPipeline(pipeline);
}
glBindProgramPipelineCallback glBindProgramPipeline = glBindProgramPipelineDispatcher;

void glBindRenderbufferDispatcher(GLenum target,GLuint renderbuffer){
	glBindRenderbuffer = reinterpret_cast<glBindRenderbufferCallback>(OpenGLGetProcAddress("glBindRenderbuffer"));
	glBindRenderbuffer(target,renderbuffer);
}
glBindRenderbufferCallback glBindRenderbuffer = glBindRenderbufferDispatcher;

void glBindSamplerDispatcher(GLuint unit,GLuint sampler){
	glBindSampler = reinterpret_cast<glBindSamplerCallback>(OpenGLGetProcAddress("glBindSampler"));
	glBindSampler(unit,sampler);
}
glBindSamplerCallback glBindSampler = glBindSamplerDispatcher;

void glBindSamplersDispatcher(GLuint first,GLsizei count,const GLuint * samplers){
	glBindSamplers = reinterpret_cast<glBindSamplersCallback>(OpenGLGetProcAddress("glBindSamplers"));
	glBindSamplers(first,count,samplers);
}
glBindSamplersCallback glBindSamplers = glBindSamplersDispatcher;

void glBindTextureDispatcher(GLenum target,GLuint texture){
	glBindTexture = reinterpret_cast<glBindTextureCallback>(OpenGLGetProcAddress("glBindTexture"));
	glBindTexture(target,texture);
}
glBindTextureCallback glBindTexture = glBindTextureDispatcher;

void glBindTextureUnitDispatcher(GLuint unit,GLuint texture){
	glBindTextureUnit = reinterpret_cast<glBindTextureUnitCallback>(OpenGLGetProcAddress("glBindTextureUnit"));
	glBindTextureUnit(unit,texture);
}
glBindTextureUnitCallback glBindTextureUnit = glBindTextureUnitDispatcher;

void glBindTexturesDispatcher(GLuint first,GLsizei count,const GLuint * textures){
	glBindTextures = reinterpret_cast<glBindTexturesCallback>(OpenGLGetProcAddress("glBindTextures"));
	glBindTextures(first,count,textures);
}
glBindTexturesCallback glBindTextures = glBindTexturesDispatcher;

void glBindTransformFeedbackDispatcher(GLenum target,GLuint id){
	glBindTransformFeedback = reinterpret_cast<glBindTransformFeedbackCallback>(OpenGLGetProcAddress("glBindTransformFeedback"));
	glBindTransformFeedback(target,id);
}
glBindTransformFeedbackCallback glBindTransformFeedback = glBindTransformFeedbackDispatcher;

void glBindVertexArrayDispatcher(GLuint array){
	glBindVertexArray = reinterpret_cast<glBindVertexArrayCallback>(OpenGLGetProcAddress("glBindVertexArray"));
	glBindVertexArray(array);
}
glBindVertexArrayCallback glBindVertexArray = glBindVertexArrayDispatcher;

void glBindVertexBufferDispatcher(GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride){
	glBindVertexBuffer = reinterpret_cast<glBindVertexBufferCallback>(OpenGLGetProcAddress("glBindVertexBuffer"));
	glBindVertexBuffer(bindingindex,buffer,offset,stride);
}
glBindVertexBufferCallback glBindVertexBuffer = glBindVertexBufferDispatcher;

void glBindVertexBuffersDispatcher(GLuint first,GLsizei count,const GLuint * buffers,const GLintptr * offsets,const GLsizei * strides){
	glBindVertexBuffers = reinterpret_cast<glBindVertexBuffersCallback>(OpenGLGetProcAddress("glBindVertexBuffers"));
	glBindVertexBuffers(first,count,buffers,offsets,strides);
}
glBindVertexBuffersCallback glBindVertexBuffers = glBindVertexBuffersDispatcher;

void glBitmapDispatcher(GLsizei width,GLsizei height,GLfloat xorig,GLfloat yorig,GLfloat xmove,GLfloat ymove,const GLubyte * bitmap){
	glBitmap = reinterpret_cast<glBitmapCallback>(OpenGLGetProcAddress("glBitmap"));
	glBitmap(width,height,xorig,yorig,xmove,ymove,bitmap);
}
glBitmapCallback glBitmap = glBitmapDispatcher;

void glBlendColorDispatcher(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){
	glBlendColor = reinterpret_cast<glBlendColorCallback>(OpenGLGetProcAddress("glBlendColor"));
	glBlendColor(red,green,blue,alpha);
}
glBlendColorCallback glBlendColor = glBlendColorDispatcher;

void glBlendEquationDispatcher(GLenum mode){
	glBlendEquation = reinterpret_cast<glBlendEquationCallback>(OpenGLGetProcAddress("glBlendEquation"));
	glBlendEquation(mode);
}
glBlendEquationCallback glBlendEquation = glBlendEquationDispatcher;

void glBlendEquationSeparateDispatcher(GLenum modeRGB,GLenum modeAlpha){
	glBlendEquationSeparate = reinterpret_cast<glBlendEquationSeparateCallback>(OpenGLGetProcAddress("glBlendEquationSeparate"));
	glBlendEquationSeparate(modeRGB,modeAlpha);
}
glBlendEquationSeparateCallback glBlendEquationSeparate = glBlendEquationSeparateDispatcher;

void glBlendEquationSeparateiDispatcher(GLuint buf,GLenum modeRGB,GLenum modeAlpha){
	glBlendEquationSeparatei = reinterpret_cast<glBlendEquationSeparateiCallback>(OpenGLGetProcAddress("glBlendEquationSeparatei"));
	glBlendEquationSeparatei(buf,modeRGB,modeAlpha);
}
glBlendEquationSeparateiCallback glBlendEquationSeparatei = glBlendEquationSeparateiDispatcher;

void glBlendEquationiDispatcher(GLuint buf,GLenum mode){
	glBlendEquationi = reinterpret_cast<glBlendEquationiCallback>(OpenGLGetProcAddress("glBlendEquationi"));
	glBlendEquationi(buf,mode);
}
glBlendEquationiCallback glBlendEquationi = glBlendEquationiDispatcher;

void glBlendFuncDispatcher(GLenum sfactor,GLenum dfactor){
	glBlendFunc = reinterpret_cast<glBlendFuncCallback>(OpenGLGetProcAddress("glBlendFunc"));
	glBlendFunc(sfactor,dfactor);
}
glBlendFuncCallback glBlendFunc = glBlendFuncDispatcher;

void glBlendFuncSeparateDispatcher(GLenum sfactorRGB,GLenum dfactorRGB,GLenum sfactorAlpha,GLenum dfactorAlpha){
	glBlendFuncSeparate = reinterpret_cast<glBlendFuncSeparateCallback>(OpenGLGetProcAddress("glBlendFuncSeparate"));
	glBlendFuncSeparate(sfactorRGB,dfactorRGB,sfactorAlpha,dfactorAlpha);
}
glBlendFuncSeparateCallback glBlendFuncSeparate = glBlendFuncSeparateDispatcher;

void glBlendFuncSeparateiDispatcher(GLuint buf,GLenum srcRGB,GLenum dstRGB,GLenum srcAlpha,GLenum dstAlpha){
	glBlendFuncSeparatei = reinterpret_cast<glBlendFuncSeparateiCallback>(OpenGLGetProcAddress("glBlendFuncSeparatei"));
	glBlendFuncSeparatei(buf,srcRGB,dstRGB,srcAlpha,dstAlpha);
}
glBlendFuncSeparateiCallback glBlendFuncSeparatei = glBlendFuncSeparateiDispatcher;

void glBlendFunciDispatcher(GLuint buf,GLenum src,GLenum dst){
	glBlendFunci = reinterpret_cast<glBlendFunciCallback>(OpenGLGetProcAddress("glBlendFunci"));
	glBlendFunci(buf,src,dst);
}
glBlendFunciCallback glBlendFunci = glBlendFunciDispatcher;

void glBlitFramebufferDispatcher(GLint srcX0,GLint srcY0,GLint srcX1,GLint srcY1,GLint dstX0,GLint dstY0,GLint dstX1,GLint dstY1,GLbitfield mask,GLenum filter){
	glBlitFramebuffer = reinterpret_cast<glBlitFramebufferCallback>(OpenGLGetProcAddress("glBlitFramebuffer"));
	glBlitFramebuffer(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);
}
glBlitFramebufferCallback glBlitFramebuffer = glBlitFramebufferDispatcher;

void glBlitNamedFramebufferDispatcher(GLuint readFramebuffer,GLuint drawFramebuffer,GLint srcX0,GLint srcY0,GLint srcX1,GLint srcY1,GLint dstX0,GLint dstY0,GLint dstX1,GLint dstY1,GLbitfield mask,GLenum filter){
	glBlitNamedFramebuffer = reinterpret_cast<glBlitNamedFramebufferCallback>(OpenGLGetProcAddress("glBlitNamedFramebuffer"));
	glBlitNamedFramebuffer(readFramebuffer,drawFramebuffer,srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);
}
glBlitNamedFramebufferCallback glBlitNamedFramebuffer = glBlitNamedFramebufferDispatcher;

void glBufferDataDispatcher(GLenum target,GLsizeiptr size,const void * data,GLenum usage){
	glBufferData = reinterpret_cast<glBufferDataCallback>(OpenGLGetProcAddress("glBufferData"));
	glBufferData(target,size,data,usage);
}
glBufferDataCallback glBufferData = glBufferDataDispatcher;

void glBufferStorageDispatcher(GLenum target,GLsizeiptr size,const void * data,GLbitfield flags){
	glBufferStorage = reinterpret_cast<glBufferStorageCallback>(OpenGLGetProcAddress("glBufferStorage"));
	glBufferStorage(target,size,data,flags);
}
glBufferStorageCallback glBufferStorage = glBufferStorageDispatcher;

void glBufferSubDataDispatcher(GLenum target,GLintptr offset,GLsizeiptr size,const void * data){
	glBufferSubData = reinterpret_cast<glBufferSubDataCallback>(OpenGLGetProcAddress("glBufferSubData"));
	glBufferSubData(target,offset,size,data);
}
glBufferSubDataCallback glBufferSubData = glBufferSubDataDispatcher;

void glCallListDispatcher(GLuint list){
	glCallList = reinterpret_cast<glCallListCallback>(OpenGLGetProcAddress("glCallList"));
	glCallList(list);
}
glCallListCallback glCallList = glCallListDispatcher;

void glCallListsDispatcher(GLsizei n,GLenum type,const void * lists){
	glCallLists = reinterpret_cast<glCallListsCallback>(OpenGLGetProcAddress("glCallLists"));
	glCallLists(n,type,lists);
}
glCallListsCallback glCallLists = glCallListsDispatcher;

GLenum glCheckFramebufferStatusDispatcher(GLenum target){
	glCheckFramebufferStatus = reinterpret_cast<glCheckFramebufferStatusCallback>(OpenGLGetProcAddress("glCheckFramebufferStatus"));
	return 	glCheckFramebufferStatus(target);
}
glCheckFramebufferStatusCallback glCheckFramebufferStatus = glCheckFramebufferStatusDispatcher;

GLenum glCheckNamedFramebufferStatusDispatcher(GLuint framebuffer,GLenum target){
	glCheckNamedFramebufferStatus = reinterpret_cast<glCheckNamedFramebufferStatusCallback>(OpenGLGetProcAddress("glCheckNamedFramebufferStatus"));
	return 	glCheckNamedFramebufferStatus(framebuffer,target);
}
glCheckNamedFramebufferStatusCallback glCheckNamedFramebufferStatus = glCheckNamedFramebufferStatusDispatcher;

void glClampColorDispatcher(GLenum target,GLenum clamp){
	glClampColor = reinterpret_cast<glClampColorCallback>(OpenGLGetProcAddress("glClampColor"));
	glClampColor(target,clamp);
}
glClampColorCallback glClampColor = glClampColorDispatcher;

void glClearDispatcher(GLbitfield mask){
	glClear = reinterpret_cast<glClearCallback>(OpenGLGetProcAddress("glClear"));
	glClear(mask);
}
glClearCallback glClear = glClearDispatcher;

void glClearAccumDispatcher(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){
	glClearAccum = reinterpret_cast<glClearAccumCallback>(OpenGLGetProcAddress("glClearAccum"));
	glClearAccum(red,green,blue,alpha);
}
glClearAccumCallback glClearAccum = glClearAccumDispatcher;

void glClearBufferDataDispatcher(GLenum target,GLenum internalformat,GLenum format,GLenum type,const void * data){
	glClearBufferData = reinterpret_cast<glClearBufferDataCallback>(OpenGLGetProcAddress("glClearBufferData"));
	glClearBufferData(target,internalformat,format,type,data);
}
glClearBufferDataCallback glClearBufferData = glClearBufferDataDispatcher;

void glClearBufferSubDataDispatcher(GLenum target,GLenum internalformat,GLintptr offset,GLsizeiptr size,GLenum format,GLenum type,const void * data){
	glClearBufferSubData = reinterpret_cast<glClearBufferSubDataCallback>(OpenGLGetProcAddress("glClearBufferSubData"));
	glClearBufferSubData(target,internalformat,offset,size,format,type,data);
}
glClearBufferSubDataCallback glClearBufferSubData = glClearBufferSubDataDispatcher;

void glClearBufferfiDispatcher(GLenum buffer,GLint drawbuffer,GLfloat depth,GLint stencil){
	glClearBufferfi = reinterpret_cast<glClearBufferfiCallback>(OpenGLGetProcAddress("glClearBufferfi"));
	glClearBufferfi(buffer,drawbuffer,depth,stencil);
}
glClearBufferfiCallback glClearBufferfi = glClearBufferfiDispatcher;

void glClearBufferfvDispatcher(GLenum buffer,GLint drawbuffer,const GLfloat * value){
	glClearBufferfv = reinterpret_cast<glClearBufferfvCallback>(OpenGLGetProcAddress("glClearBufferfv"));
	glClearBufferfv(buffer,drawbuffer,value);
}
glClearBufferfvCallback glClearBufferfv = glClearBufferfvDispatcher;

void glClearBufferivDispatcher(GLenum buffer,GLint drawbuffer,const GLint * value){
	glClearBufferiv = reinterpret_cast<glClearBufferivCallback>(OpenGLGetProcAddress("glClearBufferiv"));
	glClearBufferiv(buffer,drawbuffer,value);
}
glClearBufferivCallback glClearBufferiv = glClearBufferivDispatcher;

void glClearBufferuivDispatcher(GLenum buffer,GLint drawbuffer,const GLuint * value){
	glClearBufferuiv = reinterpret_cast<glClearBufferuivCallback>(OpenGLGetProcAddress("glClearBufferuiv"));
	glClearBufferuiv(buffer,drawbuffer,value);
}
glClearBufferuivCallback glClearBufferuiv = glClearBufferuivDispatcher;

void glClearColorDispatcher(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){
	glClearColor = reinterpret_cast<glClearColorCallback>(OpenGLGetProcAddress("glClearColor"));
	glClearColor(red,green,blue,alpha);
}
glClearColorCallback glClearColor = glClearColorDispatcher;

void glClearDepthDispatcher(GLdouble depth){
	glClearDepth = reinterpret_cast<glClearDepthCallback>(OpenGLGetProcAddress("glClearDepth"));
	glClearDepth(depth);
}
glClearDepthCallback glClearDepth = glClearDepthDispatcher;

void glClearDepthfDispatcher(GLfloat d){
	glClearDepthf = reinterpret_cast<glClearDepthfCallback>(OpenGLGetProcAddress("glClearDepthf"));
	glClearDepthf(d);
}
glClearDepthfCallback glClearDepthf = glClearDepthfDispatcher;

void glClearIndexDispatcher(GLfloat c){
	glClearIndex = reinterpret_cast<glClearIndexCallback>(OpenGLGetProcAddress("glClearIndex"));
	glClearIndex(c);
}
glClearIndexCallback glClearIndex = glClearIndexDispatcher;

void glClearNamedBufferDataDispatcher(GLuint buffer,GLenum internalformat,GLenum format,GLenum type,const void * data){
	glClearNamedBufferData = reinterpret_cast<glClearNamedBufferDataCallback>(OpenGLGetProcAddress("glClearNamedBufferData"));
	glClearNamedBufferData(buffer,internalformat,format,type,data);
}
glClearNamedBufferDataCallback glClearNamedBufferData = glClearNamedBufferDataDispatcher;

void glClearNamedBufferSubDataDispatcher(GLuint buffer,GLenum internalformat,GLintptr offset,GLsizei size,GLenum format,GLenum type,const void * data){
	glClearNamedBufferSubData = reinterpret_cast<glClearNamedBufferSubDataCallback>(OpenGLGetProcAddress("glClearNamedBufferSubData"));
	glClearNamedBufferSubData(buffer,internalformat,offset,size,format,type,data);
}
glClearNamedBufferSubDataCallback glClearNamedBufferSubData = glClearNamedBufferSubDataDispatcher;

void glClearNamedFramebufferfiDispatcher(GLuint framebuffer,GLenum buffer,const GLfloat depth,GLint stencil){
	glClearNamedFramebufferfi = reinterpret_cast<glClearNamedFramebufferfiCallback>(OpenGLGetProcAddress("glClearNamedFramebufferfi"));
	glClearNamedFramebufferfi(framebuffer,buffer,depth,stencil);
}
glClearNamedFramebufferfiCallback glClearNamedFramebufferfi = glClearNamedFramebufferfiDispatcher;

void glClearNamedFramebufferfvDispatcher(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLfloat * value){
	glClearNamedFramebufferfv = reinterpret_cast<glClearNamedFramebufferfvCallback>(OpenGLGetProcAddress("glClearNamedFramebufferfv"));
	glClearNamedFramebufferfv(framebuffer,buffer,drawbuffer,value);
}
glClearNamedFramebufferfvCallback glClearNamedFramebufferfv = glClearNamedFramebufferfvDispatcher;

void glClearNamedFramebufferivDispatcher(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLint * value){
	glClearNamedFramebufferiv = reinterpret_cast<glClearNamedFramebufferivCallback>(OpenGLGetProcAddress("glClearNamedFramebufferiv"));
	glClearNamedFramebufferiv(framebuffer,buffer,drawbuffer,value);
}
glClearNamedFramebufferivCallback glClearNamedFramebufferiv = glClearNamedFramebufferivDispatcher;

void glClearNamedFramebufferuivDispatcher(GLuint framebuffer,GLenum buffer,GLint drawbuffer,const GLuint * value){
	glClearNamedFramebufferuiv = reinterpret_cast<glClearNamedFramebufferuivCallback>(OpenGLGetProcAddress("glClearNamedFramebufferuiv"));
	glClearNamedFramebufferuiv(framebuffer,buffer,drawbuffer,value);
}
glClearNamedFramebufferuivCallback glClearNamedFramebufferuiv = glClearNamedFramebufferuivDispatcher;

void glClearStencilDispatcher(GLint s){
	glClearStencil = reinterpret_cast<glClearStencilCallback>(OpenGLGetProcAddress("glClearStencil"));
	glClearStencil(s);
}
glClearStencilCallback glClearStencil = glClearStencilDispatcher;

void glClearTexImageDispatcher(GLuint texture,GLint level,GLenum format,GLenum type,const void * data){
	glClearTexImage = reinterpret_cast<glClearTexImageCallback>(OpenGLGetProcAddress("glClearTexImage"));
	glClearTexImage(texture,level,format,type,data);
}
glClearTexImageCallback glClearTexImage = glClearTexImageDispatcher;

void glClearTexSubImageDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void * data){
	glClearTexSubImage = reinterpret_cast<glClearTexSubImageCallback>(OpenGLGetProcAddress("glClearTexSubImage"));
	glClearTexSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,data);
}
glClearTexSubImageCallback glClearTexSubImage = glClearTexSubImageDispatcher;

void glClientActiveTextureDispatcher(GLenum texture){
	glClientActiveTexture = reinterpret_cast<glClientActiveTextureCallback>(OpenGLGetProcAddress("glClientActiveTexture"));
	glClientActiveTexture(texture);
}
glClientActiveTextureCallback glClientActiveTexture = glClientActiveTextureDispatcher;

GLenum glClientWaitSyncDispatcher(GLsync sync,GLbitfield flags,GLuint64 timeout){
	glClientWaitSync = reinterpret_cast<glClientWaitSyncCallback>(OpenGLGetProcAddress("glClientWaitSync"));
	return 	glClientWaitSync(sync,flags,timeout);
}
glClientWaitSyncCallback glClientWaitSync = glClientWaitSyncDispatcher;

void glClipControlDispatcher(GLenum origin,GLenum depth){
	glClipControl = reinterpret_cast<glClipControlCallback>(OpenGLGetProcAddress("glClipControl"));
	glClipControl(origin,depth);
}
glClipControlCallback glClipControl = glClipControlDispatcher;

void glClipPlaneDispatcher(GLenum plane,const GLdouble * equation){
	glClipPlane = reinterpret_cast<glClipPlaneCallback>(OpenGLGetProcAddress("glClipPlane"));
	glClipPlane(plane,equation);
}
glClipPlaneCallback glClipPlane = glClipPlaneDispatcher;

void glColor3bDispatcher(GLbyte red,GLbyte green,GLbyte blue){
	glColor3b = reinterpret_cast<glColor3bCallback>(OpenGLGetProcAddress("glColor3b"));
	glColor3b(red,green,blue);
}
glColor3bCallback glColor3b = glColor3bDispatcher;

void glColor3bvDispatcher(const GLbyte * v){
	glColor3bv = reinterpret_cast<glColor3bvCallback>(OpenGLGetProcAddress("glColor3bv"));
	glColor3bv(v);
}
glColor3bvCallback glColor3bv = glColor3bvDispatcher;

void glColor3dDispatcher(GLdouble red,GLdouble green,GLdouble blue){
	glColor3d = reinterpret_cast<glColor3dCallback>(OpenGLGetProcAddress("glColor3d"));
	glColor3d(red,green,blue);
}
glColor3dCallback glColor3d = glColor3dDispatcher;

void glColor3dvDispatcher(const GLdouble * v){
	glColor3dv = reinterpret_cast<glColor3dvCallback>(OpenGLGetProcAddress("glColor3dv"));
	glColor3dv(v);
}
glColor3dvCallback glColor3dv = glColor3dvDispatcher;

void glColor3fDispatcher(GLfloat red,GLfloat green,GLfloat blue){
	glColor3f = reinterpret_cast<glColor3fCallback>(OpenGLGetProcAddress("glColor3f"));
	glColor3f(red,green,blue);
}
glColor3fCallback glColor3f = glColor3fDispatcher;

void glColor3fvDispatcher(const GLfloat * v){
	glColor3fv = reinterpret_cast<glColor3fvCallback>(OpenGLGetProcAddress("glColor3fv"));
	glColor3fv(v);
}
glColor3fvCallback glColor3fv = glColor3fvDispatcher;

void glColor3iDispatcher(GLint red,GLint green,GLint blue){
	glColor3i = reinterpret_cast<glColor3iCallback>(OpenGLGetProcAddress("glColor3i"));
	glColor3i(red,green,blue);
}
glColor3iCallback glColor3i = glColor3iDispatcher;

void glColor3ivDispatcher(const GLint * v){
	glColor3iv = reinterpret_cast<glColor3ivCallback>(OpenGLGetProcAddress("glColor3iv"));
	glColor3iv(v);
}
glColor3ivCallback glColor3iv = glColor3ivDispatcher;

void glColor3sDispatcher(GLshort red,GLshort green,GLshort blue){
	glColor3s = reinterpret_cast<glColor3sCallback>(OpenGLGetProcAddress("glColor3s"));
	glColor3s(red,green,blue);
}
glColor3sCallback glColor3s = glColor3sDispatcher;

void glColor3svDispatcher(const GLshort * v){
	glColor3sv = reinterpret_cast<glColor3svCallback>(OpenGLGetProcAddress("glColor3sv"));
	glColor3sv(v);
}
glColor3svCallback glColor3sv = glColor3svDispatcher;

void glColor3ubDispatcher(GLubyte red,GLubyte green,GLubyte blue){
	glColor3ub = reinterpret_cast<glColor3ubCallback>(OpenGLGetProcAddress("glColor3ub"));
	glColor3ub(red,green,blue);
}
glColor3ubCallback glColor3ub = glColor3ubDispatcher;

void glColor3ubvDispatcher(const GLubyte * v){
	glColor3ubv = reinterpret_cast<glColor3ubvCallback>(OpenGLGetProcAddress("glColor3ubv"));
	glColor3ubv(v);
}
glColor3ubvCallback glColor3ubv = glColor3ubvDispatcher;

void glColor3uiDispatcher(GLuint red,GLuint green,GLuint blue){
	glColor3ui = reinterpret_cast<glColor3uiCallback>(OpenGLGetProcAddress("glColor3ui"));
	glColor3ui(red,green,blue);
}
glColor3uiCallback glColor3ui = glColor3uiDispatcher;

void glColor3uivDispatcher(const GLuint * v){
	glColor3uiv = reinterpret_cast<glColor3uivCallback>(OpenGLGetProcAddress("glColor3uiv"));
	glColor3uiv(v);
}
glColor3uivCallback glColor3uiv = glColor3uivDispatcher;

void glColor3usDispatcher(GLushort red,GLushort green,GLushort blue){
	glColor3us = reinterpret_cast<glColor3usCallback>(OpenGLGetProcAddress("glColor3us"));
	glColor3us(red,green,blue);
}
glColor3usCallback glColor3us = glColor3usDispatcher;

void glColor3usvDispatcher(const GLushort * v){
	glColor3usv = reinterpret_cast<glColor3usvCallback>(OpenGLGetProcAddress("glColor3usv"));
	glColor3usv(v);
}
glColor3usvCallback glColor3usv = glColor3usvDispatcher;

void glColor4bDispatcher(GLbyte red,GLbyte green,GLbyte blue,GLbyte alpha){
	glColor4b = reinterpret_cast<glColor4bCallback>(OpenGLGetProcAddress("glColor4b"));
	glColor4b(red,green,blue,alpha);
}
glColor4bCallback glColor4b = glColor4bDispatcher;

void glColor4bvDispatcher(const GLbyte * v){
	glColor4bv = reinterpret_cast<glColor4bvCallback>(OpenGLGetProcAddress("glColor4bv"));
	glColor4bv(v);
}
glColor4bvCallback glColor4bv = glColor4bvDispatcher;

void glColor4dDispatcher(GLdouble red,GLdouble green,GLdouble blue,GLdouble alpha){
	glColor4d = reinterpret_cast<glColor4dCallback>(OpenGLGetProcAddress("glColor4d"));
	glColor4d(red,green,blue,alpha);
}
glColor4dCallback glColor4d = glColor4dDispatcher;

void glColor4dvDispatcher(const GLdouble * v){
	glColor4dv = reinterpret_cast<glColor4dvCallback>(OpenGLGetProcAddress("glColor4dv"));
	glColor4dv(v);
}
glColor4dvCallback glColor4dv = glColor4dvDispatcher;

void glColor4fDispatcher(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){
	glColor4f = reinterpret_cast<glColor4fCallback>(OpenGLGetProcAddress("glColor4f"));
	glColor4f(red,green,blue,alpha);
}
glColor4fCallback glColor4f = glColor4fDispatcher;

void glColor4fvDispatcher(const GLfloat * v){
	glColor4fv = reinterpret_cast<glColor4fvCallback>(OpenGLGetProcAddress("glColor4fv"));
	glColor4fv(v);
}
glColor4fvCallback glColor4fv = glColor4fvDispatcher;

void glColor4iDispatcher(GLint red,GLint green,GLint blue,GLint alpha){
	glColor4i = reinterpret_cast<glColor4iCallback>(OpenGLGetProcAddress("glColor4i"));
	glColor4i(red,green,blue,alpha);
}
glColor4iCallback glColor4i = glColor4iDispatcher;

void glColor4ivDispatcher(const GLint * v){
	glColor4iv = reinterpret_cast<glColor4ivCallback>(OpenGLGetProcAddress("glColor4iv"));
	glColor4iv(v);
}
glColor4ivCallback glColor4iv = glColor4ivDispatcher;

void glColor4sDispatcher(GLshort red,GLshort green,GLshort blue,GLshort alpha){
	glColor4s = reinterpret_cast<glColor4sCallback>(OpenGLGetProcAddress("glColor4s"));
	glColor4s(red,green,blue,alpha);
}
glColor4sCallback glColor4s = glColor4sDispatcher;

void glColor4svDispatcher(const GLshort * v){
	glColor4sv = reinterpret_cast<glColor4svCallback>(OpenGLGetProcAddress("glColor4sv"));
	glColor4sv(v);
}
glColor4svCallback glColor4sv = glColor4svDispatcher;

void glColor4ubDispatcher(GLubyte red,GLubyte green,GLubyte blue,GLubyte alpha){
	glColor4ub = reinterpret_cast<glColor4ubCallback>(OpenGLGetProcAddress("glColor4ub"));
	glColor4ub(red,green,blue,alpha);
}
glColor4ubCallback glColor4ub = glColor4ubDispatcher;

void glColor4ubvDispatcher(const GLubyte * v){
	glColor4ubv = reinterpret_cast<glColor4ubvCallback>(OpenGLGetProcAddress("glColor4ubv"));
	glColor4ubv(v);
}
glColor4ubvCallback glColor4ubv = glColor4ubvDispatcher;

void glColor4uiDispatcher(GLuint red,GLuint green,GLuint blue,GLuint alpha){
	glColor4ui = reinterpret_cast<glColor4uiCallback>(OpenGLGetProcAddress("glColor4ui"));
	glColor4ui(red,green,blue,alpha);
}
glColor4uiCallback glColor4ui = glColor4uiDispatcher;

void glColor4uivDispatcher(const GLuint * v){
	glColor4uiv = reinterpret_cast<glColor4uivCallback>(OpenGLGetProcAddress("glColor4uiv"));
	glColor4uiv(v);
}
glColor4uivCallback glColor4uiv = glColor4uivDispatcher;

void glColor4usDispatcher(GLushort red,GLushort green,GLushort blue,GLushort alpha){
	glColor4us = reinterpret_cast<glColor4usCallback>(OpenGLGetProcAddress("glColor4us"));
	glColor4us(red,green,blue,alpha);
}
glColor4usCallback glColor4us = glColor4usDispatcher;

void glColor4usvDispatcher(const GLushort * v){
	glColor4usv = reinterpret_cast<glColor4usvCallback>(OpenGLGetProcAddress("glColor4usv"));
	glColor4usv(v);
}
glColor4usvCallback glColor4usv = glColor4usvDispatcher;

void glColorMaskDispatcher(GLboolean red,GLboolean green,GLboolean blue,GLboolean alpha){
	glColorMask = reinterpret_cast<glColorMaskCallback>(OpenGLGetProcAddress("glColorMask"));
	glColorMask(red,green,blue,alpha);
}
glColorMaskCallback glColorMask = glColorMaskDispatcher;

void glColorMaskiDispatcher(GLuint index,GLboolean r,GLboolean g,GLboolean b,GLboolean a){
	glColorMaski = reinterpret_cast<glColorMaskiCallback>(OpenGLGetProcAddress("glColorMaski"));
	glColorMaski(index,r,g,b,a);
}
glColorMaskiCallback glColorMaski = glColorMaskiDispatcher;

void glColorMaterialDispatcher(GLenum face,GLenum mode){
	glColorMaterial = reinterpret_cast<glColorMaterialCallback>(OpenGLGetProcAddress("glColorMaterial"));
	glColorMaterial(face,mode);
}
glColorMaterialCallback glColorMaterial = glColorMaterialDispatcher;

void glColorP3uiDispatcher(GLenum type,GLuint color){
	glColorP3ui = reinterpret_cast<glColorP3uiCallback>(OpenGLGetProcAddress("glColorP3ui"));
	glColorP3ui(type,color);
}
glColorP3uiCallback glColorP3ui = glColorP3uiDispatcher;

void glColorP3uivDispatcher(GLenum type,const GLuint * color){
	glColorP3uiv = reinterpret_cast<glColorP3uivCallback>(OpenGLGetProcAddress("glColorP3uiv"));
	glColorP3uiv(type,color);
}
glColorP3uivCallback glColorP3uiv = glColorP3uivDispatcher;

void glColorP4uiDispatcher(GLenum type,GLuint color){
	glColorP4ui = reinterpret_cast<glColorP4uiCallback>(OpenGLGetProcAddress("glColorP4ui"));
	glColorP4ui(type,color);
}
glColorP4uiCallback glColorP4ui = glColorP4uiDispatcher;

void glColorP4uivDispatcher(GLenum type,const GLuint * color){
	glColorP4uiv = reinterpret_cast<glColorP4uivCallback>(OpenGLGetProcAddress("glColorP4uiv"));
	glColorP4uiv(type,color);
}
glColorP4uivCallback glColorP4uiv = glColorP4uivDispatcher;

void glColorPointerDispatcher(GLint size,GLenum type,GLsizei stride,const void * pointer){
	glColorPointer = reinterpret_cast<glColorPointerCallback>(OpenGLGetProcAddress("glColorPointer"));
	glColorPointer(size,type,stride,pointer);
}
glColorPointerCallback glColorPointer = glColorPointerDispatcher;

void glCompileShaderDispatcher(GLuint shader){
	glCompileShader = reinterpret_cast<glCompileShaderCallback>(OpenGLGetProcAddress("glCompileShader"));
	glCompileShader(shader);
}
glCompileShaderCallback glCompileShader = glCompileShaderDispatcher;

void glCompressedTexImage1DDispatcher(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLint border,GLsizei imageSize,const void * data){
	glCompressedTexImage1D = reinterpret_cast<glCompressedTexImage1DCallback>(OpenGLGetProcAddress("glCompressedTexImage1D"));
	glCompressedTexImage1D(target,level,internalformat,width,border,imageSize,data);
}
glCompressedTexImage1DCallback glCompressedTexImage1D = glCompressedTexImage1DDispatcher;

void glCompressedTexImage2DDispatcher(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,const void * data){
	glCompressedTexImage2D = reinterpret_cast<glCompressedTexImage2DCallback>(OpenGLGetProcAddress("glCompressedTexImage2D"));
	glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,data);
}
glCompressedTexImage2DCallback glCompressedTexImage2D = glCompressedTexImage2DDispatcher;

void glCompressedTexImage3DDispatcher(GLenum target,GLint level,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,const void * data){
	glCompressedTexImage3D = reinterpret_cast<glCompressedTexImage3DCallback>(OpenGLGetProcAddress("glCompressedTexImage3D"));
	glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imageSize,data);
}
glCompressedTexImage3DCallback glCompressedTexImage3D = glCompressedTexImage3DDispatcher;

void glCompressedTexSubImage1DDispatcher(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void * data){
	glCompressedTexSubImage1D = reinterpret_cast<glCompressedTexSubImage1DCallback>(OpenGLGetProcAddress("glCompressedTexSubImage1D"));
	glCompressedTexSubImage1D(target,level,xoffset,width,format,imageSize,data);
}
glCompressedTexSubImage1DCallback glCompressedTexSubImage1D = glCompressedTexSubImage1DDispatcher;

void glCompressedTexSubImage2DDispatcher(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void * data){
	glCompressedTexSubImage2D = reinterpret_cast<glCompressedTexSubImage2DCallback>(OpenGLGetProcAddress("glCompressedTexSubImage2D"));
	glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imageSize,data);
}
glCompressedTexSubImage2DCallback glCompressedTexSubImage2D = glCompressedTexSubImage2DDispatcher;

void glCompressedTexSubImage3DDispatcher(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void * data){
	glCompressedTexSubImage3D = reinterpret_cast<glCompressedTexSubImage3DCallback>(OpenGLGetProcAddress("glCompressedTexSubImage3D"));
	glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);
}
glCompressedTexSubImage3DCallback glCompressedTexSubImage3D = glCompressedTexSubImage3DDispatcher;

void glCompressedTextureSubImage1DDispatcher(GLuint texture,GLint level,GLint xoffset,GLsizei width,GLenum format,GLsizei imageSize,const void * data){
	glCompressedTextureSubImage1D = reinterpret_cast<glCompressedTextureSubImage1DCallback>(OpenGLGetProcAddress("glCompressedTextureSubImage1D"));
	glCompressedTextureSubImage1D(texture,level,xoffset,width,format,imageSize,data);
}
glCompressedTextureSubImage1DCallback glCompressedTextureSubImage1D = glCompressedTextureSubImage1DDispatcher;

void glCompressedTextureSubImage2DDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLsizei imageSize,const void * data){
	glCompressedTextureSubImage2D = reinterpret_cast<glCompressedTextureSubImage2DCallback>(OpenGLGetProcAddress("glCompressedTextureSubImage2D"));
	glCompressedTextureSubImage2D(texture,level,xoffset,yoffset,width,height,format,imageSize,data);
}
glCompressedTextureSubImage2DCallback glCompressedTextureSubImage2D = glCompressedTextureSubImage2DDispatcher;

void glCompressedTextureSubImage3DDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLsizei imageSize,const void * data){
	glCompressedTextureSubImage3D = reinterpret_cast<glCompressedTextureSubImage3DCallback>(OpenGLGetProcAddress("glCompressedTextureSubImage3D"));
	glCompressedTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);
}
glCompressedTextureSubImage3DCallback glCompressedTextureSubImage3D = glCompressedTextureSubImage3DDispatcher;

void glCopyBufferSubDataDispatcher(GLenum readTarget,GLenum writeTarget,GLintptr readOffset,GLintptr writeOffset,GLsizeiptr size){
	glCopyBufferSubData = reinterpret_cast<glCopyBufferSubDataCallback>(OpenGLGetProcAddress("glCopyBufferSubData"));
	glCopyBufferSubData(readTarget,writeTarget,readOffset,writeOffset,size);
}
glCopyBufferSubDataCallback glCopyBufferSubData = glCopyBufferSubDataDispatcher;

void glCopyImageSubDataDispatcher(GLuint srcName,GLenum srcTarget,GLint srcLevel,GLint srcX,GLint srcY,GLint srcZ,GLuint dstName,GLenum dstTarget,GLint dstLevel,GLint dstX,GLint dstY,GLint dstZ,GLsizei srcWidth,GLsizei srcHeight,GLsizei srcDepth){
	glCopyImageSubData = reinterpret_cast<glCopyImageSubDataCallback>(OpenGLGetProcAddress("glCopyImageSubData"));
	glCopyImageSubData(srcName,srcTarget,srcLevel,srcX,srcY,srcZ,dstName,dstTarget,dstLevel,dstX,dstY,dstZ,srcWidth,srcHeight,srcDepth);
}
glCopyImageSubDataCallback glCopyImageSubData = glCopyImageSubDataDispatcher;

void glCopyNamedBufferSubDataDispatcher(GLuint readBuffer,GLuint writeBuffer,GLintptr readOffset,GLintptr writeOffset,GLsizei size){
	glCopyNamedBufferSubData = reinterpret_cast<glCopyNamedBufferSubDataCallback>(OpenGLGetProcAddress("glCopyNamedBufferSubData"));
	glCopyNamedBufferSubData(readBuffer,writeBuffer,readOffset,writeOffset,size);
}
glCopyNamedBufferSubDataCallback glCopyNamedBufferSubData = glCopyNamedBufferSubDataDispatcher;

void glCopyPixelsDispatcher(GLint x,GLint y,GLsizei width,GLsizei height,GLenum type){
	glCopyPixels = reinterpret_cast<glCopyPixelsCallback>(OpenGLGetProcAddress("glCopyPixels"));
	glCopyPixels(x,y,width,height,type);
}
glCopyPixelsCallback glCopyPixels = glCopyPixelsDispatcher;

void glCopyTexImage1DDispatcher(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLint border){
	glCopyTexImage1D = reinterpret_cast<glCopyTexImage1DCallback>(OpenGLGetProcAddress("glCopyTexImage1D"));
	glCopyTexImage1D(target,level,internalformat,x,y,width,border);
}
glCopyTexImage1DCallback glCopyTexImage1D = glCopyTexImage1DDispatcher;

void glCopyTexImage2DDispatcher(GLenum target,GLint level,GLenum internalformat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border){
	glCopyTexImage2D = reinterpret_cast<glCopyTexImage2DCallback>(OpenGLGetProcAddress("glCopyTexImage2D"));
	glCopyTexImage2D(target,level,internalformat,x,y,width,height,border);
}
glCopyTexImage2DCallback glCopyTexImage2D = glCopyTexImage2DDispatcher;

void glCopyTexSubImage1DDispatcher(GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width){
	glCopyTexSubImage1D = reinterpret_cast<glCopyTexSubImage1DCallback>(OpenGLGetProcAddress("glCopyTexSubImage1D"));
	glCopyTexSubImage1D(target,level,xoffset,x,y,width);
}
glCopyTexSubImage1DCallback glCopyTexSubImage1D = glCopyTexSubImage1DDispatcher;

void glCopyTexSubImage2DDispatcher(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height){
	glCopyTexSubImage2D = reinterpret_cast<glCopyTexSubImage2DCallback>(OpenGLGetProcAddress("glCopyTexSubImage2D"));
	glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height);
}
glCopyTexSubImage2DCallback glCopyTexSubImage2D = glCopyTexSubImage2DDispatcher;

void glCopyTexSubImage3DDispatcher(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height){
	glCopyTexSubImage3D = reinterpret_cast<glCopyTexSubImage3DCallback>(OpenGLGetProcAddress("glCopyTexSubImage3D"));
	glCopyTexSubImage3D(target,level,xoffset,yoffset,zoffset,x,y,width,height);
}
glCopyTexSubImage3DCallback glCopyTexSubImage3D = glCopyTexSubImage3DDispatcher;

void glCopyTextureSubImage1DDispatcher(GLuint texture,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width){
	glCopyTextureSubImage1D = reinterpret_cast<glCopyTextureSubImage1DCallback>(OpenGLGetProcAddress("glCopyTextureSubImage1D"));
	glCopyTextureSubImage1D(texture,level,xoffset,x,y,width);
}
glCopyTextureSubImage1DCallback glCopyTextureSubImage1D = glCopyTextureSubImage1DDispatcher;

void glCopyTextureSubImage2DDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height){
	glCopyTextureSubImage2D = reinterpret_cast<glCopyTextureSubImage2DCallback>(OpenGLGetProcAddress("glCopyTextureSubImage2D"));
	glCopyTextureSubImage2D(texture,level,xoffset,yoffset,x,y,width,height);
}
glCopyTextureSubImage2DCallback glCopyTextureSubImage2D = glCopyTextureSubImage2DDispatcher;

void glCopyTextureSubImage3DDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLint x,GLint y,GLsizei width,GLsizei height){
	glCopyTextureSubImage3D = reinterpret_cast<glCopyTextureSubImage3DCallback>(OpenGLGetProcAddress("glCopyTextureSubImage3D"));
	glCopyTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,x,y,width,height);
}
glCopyTextureSubImage3DCallback glCopyTextureSubImage3D = glCopyTextureSubImage3DDispatcher;

void glCreateBuffersDispatcher(GLsizei n,GLuint * buffers){
	glCreateBuffers = reinterpret_cast<glCreateBuffersCallback>(OpenGLGetProcAddress("glCreateBuffers"));
	glCreateBuffers(n,buffers);
}
glCreateBuffersCallback glCreateBuffers = glCreateBuffersDispatcher;

void glCreateFramebuffersDispatcher(GLsizei n,GLuint * framebuffers){
	glCreateFramebuffers = reinterpret_cast<glCreateFramebuffersCallback>(OpenGLGetProcAddress("glCreateFramebuffers"));
	glCreateFramebuffers(n,framebuffers);
}
glCreateFramebuffersCallback glCreateFramebuffers = glCreateFramebuffersDispatcher;

GLuint glCreateProgramDispatcher(){
	glCreateProgram = reinterpret_cast<glCreateProgramCallback>(OpenGLGetProcAddress("glCreateProgram"));
	return 	glCreateProgram();
}
glCreateProgramCallback glCreateProgram = glCreateProgramDispatcher;

void glCreateProgramPipelinesDispatcher(GLsizei n,GLuint * pipelines){
	glCreateProgramPipelines = reinterpret_cast<glCreateProgramPipelinesCallback>(OpenGLGetProcAddress("glCreateProgramPipelines"));
	glCreateProgramPipelines(n,pipelines);
}
glCreateProgramPipelinesCallback glCreateProgramPipelines = glCreateProgramPipelinesDispatcher;

void glCreateQueriesDispatcher(GLenum target,GLsizei n,GLuint * ids){
	glCreateQueries = reinterpret_cast<glCreateQueriesCallback>(OpenGLGetProcAddress("glCreateQueries"));
	glCreateQueries(target,n,ids);
}
glCreateQueriesCallback glCreateQueries = glCreateQueriesDispatcher;

void glCreateRenderbuffersDispatcher(GLsizei n,GLuint * renderbuffers){
	glCreateRenderbuffers = reinterpret_cast<glCreateRenderbuffersCallback>(OpenGLGetProcAddress("glCreateRenderbuffers"));
	glCreateRenderbuffers(n,renderbuffers);
}
glCreateRenderbuffersCallback glCreateRenderbuffers = glCreateRenderbuffersDispatcher;

void glCreateSamplersDispatcher(GLsizei n,GLuint * samplers){
	glCreateSamplers = reinterpret_cast<glCreateSamplersCallback>(OpenGLGetProcAddress("glCreateSamplers"));
	glCreateSamplers(n,samplers);
}
glCreateSamplersCallback glCreateSamplers = glCreateSamplersDispatcher;

GLuint glCreateShaderDispatcher(GLenum type){
	glCreateShader = reinterpret_cast<glCreateShaderCallback>(OpenGLGetProcAddress("glCreateShader"));
	return 	glCreateShader(type);
}
glCreateShaderCallback glCreateShader = glCreateShaderDispatcher;

GLuint glCreateShaderProgramvDispatcher(GLenum type,GLsizei count,const GLchar *const* strings){
	glCreateShaderProgramv = reinterpret_cast<glCreateShaderProgramvCallback>(OpenGLGetProcAddress("glCreateShaderProgramv"));
	return 	glCreateShaderProgramv(type,count,strings);
}
glCreateShaderProgramvCallback glCreateShaderProgramv = glCreateShaderProgramvDispatcher;

void glCreateTexturesDispatcher(GLenum target,GLsizei n,GLuint * textures){
	glCreateTextures = reinterpret_cast<glCreateTexturesCallback>(OpenGLGetProcAddress("glCreateTextures"));
	glCreateTextures(target,n,textures);
}
glCreateTexturesCallback glCreateTextures = glCreateTexturesDispatcher;

void glCreateTransformFeedbacksDispatcher(GLsizei n,GLuint * ids){
	glCreateTransformFeedbacks = reinterpret_cast<glCreateTransformFeedbacksCallback>(OpenGLGetProcAddress("glCreateTransformFeedbacks"));
	glCreateTransformFeedbacks(n,ids);
}
glCreateTransformFeedbacksCallback glCreateTransformFeedbacks = glCreateTransformFeedbacksDispatcher;

void glCreateVertexArraysDispatcher(GLsizei n,GLuint * arrays){
	glCreateVertexArrays = reinterpret_cast<glCreateVertexArraysCallback>(OpenGLGetProcAddress("glCreateVertexArrays"));
	glCreateVertexArrays(n,arrays);
}
glCreateVertexArraysCallback glCreateVertexArrays = glCreateVertexArraysDispatcher;

void glCullFaceDispatcher(GLenum mode){
	glCullFace = reinterpret_cast<glCullFaceCallback>(OpenGLGetProcAddress("glCullFace"));
	glCullFace(mode);
}
glCullFaceCallback glCullFace = glCullFaceDispatcher;

void glDebugMessageCallbackDispatcher(GLDEBUGPROC callback,const void * userParam){
	glDebugMessageCallback = reinterpret_cast<glDebugMessageCallbackCallback>(OpenGLGetProcAddress("glDebugMessageCallback"));
	glDebugMessageCallback(callback,userParam);
}
glDebugMessageCallbackCallback glDebugMessageCallback = glDebugMessageCallbackDispatcher;

void glDebugMessageControlDispatcher(GLenum source,GLenum type,GLenum severity,GLsizei count,const GLuint * ids,GLboolean enabled){
	glDebugMessageControl = reinterpret_cast<glDebugMessageControlCallback>(OpenGLGetProcAddress("glDebugMessageControl"));
	glDebugMessageControl(source,type,severity,count,ids,enabled);
}
glDebugMessageControlCallback glDebugMessageControl = glDebugMessageControlDispatcher;

void glDebugMessageInsertDispatcher(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar * buf){
	glDebugMessageInsert = reinterpret_cast<glDebugMessageInsertCallback>(OpenGLGetProcAddress("glDebugMessageInsert"));
	glDebugMessageInsert(source,type,id,severity,length,buf);
}
glDebugMessageInsertCallback glDebugMessageInsert = glDebugMessageInsertDispatcher;

void glDeleteBuffersDispatcher(GLsizei n,const GLuint * buffers){
	glDeleteBuffers = reinterpret_cast<glDeleteBuffersCallback>(OpenGLGetProcAddress("glDeleteBuffers"));
	glDeleteBuffers(n,buffers);
}
glDeleteBuffersCallback glDeleteBuffers = glDeleteBuffersDispatcher;

void glDeleteFramebuffersDispatcher(GLsizei n,const GLuint * framebuffers){
	glDeleteFramebuffers = reinterpret_cast<glDeleteFramebuffersCallback>(OpenGLGetProcAddress("glDeleteFramebuffers"));
	glDeleteFramebuffers(n,framebuffers);
}
glDeleteFramebuffersCallback glDeleteFramebuffers = glDeleteFramebuffersDispatcher;

void glDeleteListsDispatcher(GLuint list,GLsizei range){
	glDeleteLists = reinterpret_cast<glDeleteListsCallback>(OpenGLGetProcAddress("glDeleteLists"));
	glDeleteLists(list,range);
}
glDeleteListsCallback glDeleteLists = glDeleteListsDispatcher;

void glDeleteProgramDispatcher(GLuint program){
	glDeleteProgram = reinterpret_cast<glDeleteProgramCallback>(OpenGLGetProcAddress("glDeleteProgram"));
	glDeleteProgram(program);
}
glDeleteProgramCallback glDeleteProgram = glDeleteProgramDispatcher;

void glDeleteProgramPipelinesDispatcher(GLsizei n,const GLuint * pipelines){
	glDeleteProgramPipelines = reinterpret_cast<glDeleteProgramPipelinesCallback>(OpenGLGetProcAddress("glDeleteProgramPipelines"));
	glDeleteProgramPipelines(n,pipelines);
}
glDeleteProgramPipelinesCallback glDeleteProgramPipelines = glDeleteProgramPipelinesDispatcher;

void glDeleteQueriesDispatcher(GLsizei n,const GLuint * ids){
	glDeleteQueries = reinterpret_cast<glDeleteQueriesCallback>(OpenGLGetProcAddress("glDeleteQueries"));
	glDeleteQueries(n,ids);
}
glDeleteQueriesCallback glDeleteQueries = glDeleteQueriesDispatcher;

void glDeleteRenderbuffersDispatcher(GLsizei n,const GLuint * renderbuffers){
	glDeleteRenderbuffers = reinterpret_cast<glDeleteRenderbuffersCallback>(OpenGLGetProcAddress("glDeleteRenderbuffers"));
	glDeleteRenderbuffers(n,renderbuffers);
}
glDeleteRenderbuffersCallback glDeleteRenderbuffers = glDeleteRenderbuffersDispatcher;

void glDeleteSamplersDispatcher(GLsizei count,const GLuint * samplers){
	glDeleteSamplers = reinterpret_cast<glDeleteSamplersCallback>(OpenGLGetProcAddress("glDeleteSamplers"));
	glDeleteSamplers(count,samplers);
}
glDeleteSamplersCallback glDeleteSamplers = glDeleteSamplersDispatcher;

void glDeleteShaderDispatcher(GLuint shader){
	glDeleteShader = reinterpret_cast<glDeleteShaderCallback>(OpenGLGetProcAddress("glDeleteShader"));
	glDeleteShader(shader);
}
glDeleteShaderCallback glDeleteShader = glDeleteShaderDispatcher;

void glDeleteSyncDispatcher(GLsync sync){
	glDeleteSync = reinterpret_cast<glDeleteSyncCallback>(OpenGLGetProcAddress("glDeleteSync"));
	glDeleteSync(sync);
}
glDeleteSyncCallback glDeleteSync = glDeleteSyncDispatcher;

void glDeleteTexturesDispatcher(GLsizei n,const GLuint * textures){
	glDeleteTextures = reinterpret_cast<glDeleteTexturesCallback>(OpenGLGetProcAddress("glDeleteTextures"));
	glDeleteTextures(n,textures);
}
glDeleteTexturesCallback glDeleteTextures = glDeleteTexturesDispatcher;

void glDeleteTransformFeedbacksDispatcher(GLsizei n,const GLuint * ids){
	glDeleteTransformFeedbacks = reinterpret_cast<glDeleteTransformFeedbacksCallback>(OpenGLGetProcAddress("glDeleteTransformFeedbacks"));
	glDeleteTransformFeedbacks(n,ids);
}
glDeleteTransformFeedbacksCallback glDeleteTransformFeedbacks = glDeleteTransformFeedbacksDispatcher;

void glDeleteVertexArraysDispatcher(GLsizei n,const GLuint * arrays){
	glDeleteVertexArrays = reinterpret_cast<glDeleteVertexArraysCallback>(OpenGLGetProcAddress("glDeleteVertexArrays"));
	glDeleteVertexArrays(n,arrays);
}
glDeleteVertexArraysCallback glDeleteVertexArrays = glDeleteVertexArraysDispatcher;

void glDepthFuncDispatcher(GLenum func){
	glDepthFunc = reinterpret_cast<glDepthFuncCallback>(OpenGLGetProcAddress("glDepthFunc"));
	glDepthFunc(func);
}
glDepthFuncCallback glDepthFunc = glDepthFuncDispatcher;

void glDepthMaskDispatcher(GLboolean flag){
	glDepthMask = reinterpret_cast<glDepthMaskCallback>(OpenGLGetProcAddress("glDepthMask"));
	glDepthMask(flag);
}
glDepthMaskCallback glDepthMask = glDepthMaskDispatcher;

void glDepthRangeDispatcher(GLdouble near_,GLdouble far_){
	glDepthRange = reinterpret_cast<glDepthRangeCallback>(OpenGLGetProcAddress("glDepthRange"));
	glDepthRange(near_,far_);
}
glDepthRangeCallback glDepthRange = glDepthRangeDispatcher;

void glDepthRangeArrayvDispatcher(GLuint first,GLsizei count,const GLdouble * v){
	glDepthRangeArrayv = reinterpret_cast<glDepthRangeArrayvCallback>(OpenGLGetProcAddress("glDepthRangeArrayv"));
	glDepthRangeArrayv(first,count,v);
}
glDepthRangeArrayvCallback glDepthRangeArrayv = glDepthRangeArrayvDispatcher;

void glDepthRangeIndexedDispatcher(GLuint index,GLdouble n,GLdouble f){
	glDepthRangeIndexed = reinterpret_cast<glDepthRangeIndexedCallback>(OpenGLGetProcAddress("glDepthRangeIndexed"));
	glDepthRangeIndexed(index,n,f);
}
glDepthRangeIndexedCallback glDepthRangeIndexed = glDepthRangeIndexedDispatcher;

void glDepthRangefDispatcher(GLfloat n,GLfloat f){
	glDepthRangef = reinterpret_cast<glDepthRangefCallback>(OpenGLGetProcAddress("glDepthRangef"));
	glDepthRangef(n,f);
}
glDepthRangefCallback glDepthRangef = glDepthRangefDispatcher;

void glDetachShaderDispatcher(GLuint program,GLuint shader){
	glDetachShader = reinterpret_cast<glDetachShaderCallback>(OpenGLGetProcAddress("glDetachShader"));
	glDetachShader(program,shader);
}
glDetachShaderCallback glDetachShader = glDetachShaderDispatcher;

void glDisableDispatcher(GLenum cap){
	glDisable = reinterpret_cast<glDisableCallback>(OpenGLGetProcAddress("glDisable"));
	glDisable(cap);
}
glDisableCallback glDisable = glDisableDispatcher;

void glDisableClientStateDispatcher(GLenum array){
	glDisableClientState = reinterpret_cast<glDisableClientStateCallback>(OpenGLGetProcAddress("glDisableClientState"));
	glDisableClientState(array);
}
glDisableClientStateCallback glDisableClientState = glDisableClientStateDispatcher;

void glDisableVertexArrayAttribDispatcher(GLuint vaobj,GLuint index){
	glDisableVertexArrayAttrib = reinterpret_cast<glDisableVertexArrayAttribCallback>(OpenGLGetProcAddress("glDisableVertexArrayAttrib"));
	glDisableVertexArrayAttrib(vaobj,index);
}
glDisableVertexArrayAttribCallback glDisableVertexArrayAttrib = glDisableVertexArrayAttribDispatcher;

void glDisableVertexAttribArrayDispatcher(GLuint index){
	glDisableVertexAttribArray = reinterpret_cast<glDisableVertexAttribArrayCallback>(OpenGLGetProcAddress("glDisableVertexAttribArray"));
	glDisableVertexAttribArray(index);
}
glDisableVertexAttribArrayCallback glDisableVertexAttribArray = glDisableVertexAttribArrayDispatcher;

void glDisableiDispatcher(GLenum target,GLuint index){
	glDisablei = reinterpret_cast<glDisableiCallback>(OpenGLGetProcAddress("glDisablei"));
	glDisablei(target,index);
}
glDisableiCallback glDisablei = glDisableiDispatcher;

void glDispatchComputeDispatcher(GLuint num_groups_x,GLuint num_groups_y,GLuint num_groups_z){
	glDispatchCompute = reinterpret_cast<glDispatchComputeCallback>(OpenGLGetProcAddress("glDispatchCompute"));
	glDispatchCompute(num_groups_x,num_groups_y,num_groups_z);
}
glDispatchComputeCallback glDispatchCompute = glDispatchComputeDispatcher;

void glDispatchComputeIndirectDispatcher(GLintptr indirect){
	glDispatchComputeIndirect = reinterpret_cast<glDispatchComputeIndirectCallback>(OpenGLGetProcAddress("glDispatchComputeIndirect"));
	glDispatchComputeIndirect(indirect);
}
glDispatchComputeIndirectCallback glDispatchComputeIndirect = glDispatchComputeIndirectDispatcher;

void glDrawArraysDispatcher(GLenum mode,GLint first,GLsizei count){
	glDrawArrays = reinterpret_cast<glDrawArraysCallback>(OpenGLGetProcAddress("glDrawArrays"));
	glDrawArrays(mode,first,count);
}
glDrawArraysCallback glDrawArrays = glDrawArraysDispatcher;

void glDrawArraysIndirectDispatcher(GLenum mode,const void * indirect){
	glDrawArraysIndirect = reinterpret_cast<glDrawArraysIndirectCallback>(OpenGLGetProcAddress("glDrawArraysIndirect"));
	glDrawArraysIndirect(mode,indirect);
}
glDrawArraysIndirectCallback glDrawArraysIndirect = glDrawArraysIndirectDispatcher;

void glDrawArraysInstancedDispatcher(GLenum mode,GLint first,GLsizei count,GLsizei instancecount){
	glDrawArraysInstanced = reinterpret_cast<glDrawArraysInstancedCallback>(OpenGLGetProcAddress("glDrawArraysInstanced"));
	glDrawArraysInstanced(mode,first,count,instancecount);
}
glDrawArraysInstancedCallback glDrawArraysInstanced = glDrawArraysInstancedDispatcher;

void glDrawArraysInstancedBaseInstanceDispatcher(GLenum mode,GLint first,GLsizei count,GLsizei instancecount,GLuint baseinstance){
	glDrawArraysInstancedBaseInstance = reinterpret_cast<glDrawArraysInstancedBaseInstanceCallback>(OpenGLGetProcAddress("glDrawArraysInstancedBaseInstance"));
	glDrawArraysInstancedBaseInstance(mode,first,count,instancecount,baseinstance);
}
glDrawArraysInstancedBaseInstanceCallback glDrawArraysInstancedBaseInstance = glDrawArraysInstancedBaseInstanceDispatcher;

void glDrawBufferDispatcher(GLenum buf){
	glDrawBuffer = reinterpret_cast<glDrawBufferCallback>(OpenGLGetProcAddress("glDrawBuffer"));
	glDrawBuffer(buf);
}
glDrawBufferCallback glDrawBuffer = glDrawBufferDispatcher;

void glDrawBuffersDispatcher(GLsizei n,const GLenum * bufs){
	glDrawBuffers = reinterpret_cast<glDrawBuffersCallback>(OpenGLGetProcAddress("glDrawBuffers"));
	glDrawBuffers(n,bufs);
}
glDrawBuffersCallback glDrawBuffers = glDrawBuffersDispatcher;

void glDrawElementsDispatcher(GLenum mode,GLsizei count,GLenum type,const void * indices){
	glDrawElements = reinterpret_cast<glDrawElementsCallback>(OpenGLGetProcAddress("glDrawElements"));
	glDrawElements(mode,count,type,indices);
}
glDrawElementsCallback glDrawElements = glDrawElementsDispatcher;

void glDrawElementsBaseVertexDispatcher(GLenum mode,GLsizei count,GLenum type,const void * indices,GLint basevertex){
	glDrawElementsBaseVertex = reinterpret_cast<glDrawElementsBaseVertexCallback>(OpenGLGetProcAddress("glDrawElementsBaseVertex"));
	glDrawElementsBaseVertex(mode,count,type,indices,basevertex);
}
glDrawElementsBaseVertexCallback glDrawElementsBaseVertex = glDrawElementsBaseVertexDispatcher;

void glDrawElementsIndirectDispatcher(GLenum mode,GLenum type,const void * indirect){
	glDrawElementsIndirect = reinterpret_cast<glDrawElementsIndirectCallback>(OpenGLGetProcAddress("glDrawElementsIndirect"));
	glDrawElementsIndirect(mode,type,indirect);
}
glDrawElementsIndirectCallback glDrawElementsIndirect = glDrawElementsIndirectDispatcher;

void glDrawElementsInstancedDispatcher(GLenum mode,GLsizei count,GLenum type,const void * indices,GLsizei instancecount){
	glDrawElementsInstanced = reinterpret_cast<glDrawElementsInstancedCallback>(OpenGLGetProcAddress("glDrawElementsInstanced"));
	glDrawElementsInstanced(mode,count,type,indices,instancecount);
}
glDrawElementsInstancedCallback glDrawElementsInstanced = glDrawElementsInstancedDispatcher;

void glDrawElementsInstancedBaseInstanceDispatcher(GLenum mode,GLsizei count,GLenum type,const void * indices,GLsizei instancecount,GLuint baseinstance){
	glDrawElementsInstancedBaseInstance = reinterpret_cast<glDrawElementsInstancedBaseInstanceCallback>(OpenGLGetProcAddress("glDrawElementsInstancedBaseInstance"));
	glDrawElementsInstancedBaseInstance(mode,count,type,indices,instancecount,baseinstance);
}
glDrawElementsInstancedBaseInstanceCallback glDrawElementsInstancedBaseInstance = glDrawElementsInstancedBaseInstanceDispatcher;

void glDrawElementsInstancedBaseVertexDispatcher(GLenum mode,GLsizei count,GLenum type,const void * indices,GLsizei instancecount,GLint basevertex){
	glDrawElementsInstancedBaseVertex = reinterpret_cast<glDrawElementsInstancedBaseVertexCallback>(OpenGLGetProcAddress("glDrawElementsInstancedBaseVertex"));
	glDrawElementsInstancedBaseVertex(mode,count,type,indices,instancecount,basevertex);
}
glDrawElementsInstancedBaseVertexCallback glDrawElementsInstancedBaseVertex = glDrawElementsInstancedBaseVertexDispatcher;

void glDrawElementsInstancedBaseVertexBaseInstanceDispatcher(GLenum mode,GLsizei count,GLenum type,const void * indices,GLsizei instancecount,GLint basevertex,GLuint baseinstance){
	glDrawElementsInstancedBaseVertexBaseInstance = reinterpret_cast<glDrawElementsInstancedBaseVertexBaseInstanceCallback>(OpenGLGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance"));
	glDrawElementsInstancedBaseVertexBaseInstance(mode,count,type,indices,instancecount,basevertex,baseinstance);
}

glDrawElementsInstancedBaseVertexBaseInstanceCallback glDrawElementsInstancedBaseVertexBaseInstance = glDrawElementsInstancedBaseVertexBaseInstanceDispatcher;

void glDrawPixelsDispatcher(GLsizei width,GLsizei height,GLenum format,GLenum type,const void * pixels){
	glDrawPixels = reinterpret_cast<glDrawPixelsCallback>(OpenGLGetProcAddress("glDrawPixels"));
	glDrawPixels(width,height,format,type,pixels);
}
glDrawPixelsCallback glDrawPixels = glDrawPixelsDispatcher;

void glDrawRangeElementsDispatcher(GLenum mode,GLuint start,GLuint end,GLsizei count,GLenum type,const void * indices){
	glDrawRangeElements = reinterpret_cast<glDrawRangeElementsCallback>(OpenGLGetProcAddress("glDrawRangeElements"));
	glDrawRangeElements(mode,start,end,count,type,indices);
}
glDrawRangeElementsCallback glDrawRangeElements = glDrawRangeElementsDispatcher;

void glDrawRangeElementsBaseVertexDispatcher(GLenum mode,GLuint start,GLuint end,GLsizei count,GLenum type,const void * indices,GLint basevertex){
	glDrawRangeElementsBaseVertex = reinterpret_cast<glDrawRangeElementsBaseVertexCallback>(OpenGLGetProcAddress("glDrawRangeElementsBaseVertex"));
	glDrawRangeElementsBaseVertex(mode,start,end,count,type,indices,basevertex);
}
glDrawRangeElementsBaseVertexCallback glDrawRangeElementsBaseVertex = glDrawRangeElementsBaseVertexDispatcher;

void glDrawTransformFeedbackDispatcher(GLenum mode,GLuint id){
	glDrawTransformFeedback = reinterpret_cast<glDrawTransformFeedbackCallback>(OpenGLGetProcAddress("glDrawTransformFeedback"));
	glDrawTransformFeedback(mode,id);
}
glDrawTransformFeedbackCallback glDrawTransformFeedback = glDrawTransformFeedbackDispatcher;

void glDrawTransformFeedbackInstancedDispatcher(GLenum mode,GLuint id,GLsizei instancecount){
	glDrawTransformFeedbackInstanced = reinterpret_cast<glDrawTransformFeedbackInstancedCallback>(OpenGLGetProcAddress("glDrawTransformFeedbackInstanced"));
	glDrawTransformFeedbackInstanced(mode,id,instancecount);
}
glDrawTransformFeedbackInstancedCallback glDrawTransformFeedbackInstanced = glDrawTransformFeedbackInstancedDispatcher;

void glDrawTransformFeedbackStreamDispatcher(GLenum mode,GLuint id,GLuint stream){
	glDrawTransformFeedbackStream = reinterpret_cast<glDrawTransformFeedbackStreamCallback>(OpenGLGetProcAddress("glDrawTransformFeedbackStream"));
	glDrawTransformFeedbackStream(mode,id,stream);
}
glDrawTransformFeedbackStreamCallback glDrawTransformFeedbackStream = glDrawTransformFeedbackStreamDispatcher;

void glDrawTransformFeedbackStreamInstancedDispatcher(GLenum mode,GLuint id,GLuint stream,GLsizei instancecount){
	glDrawTransformFeedbackStreamInstanced = reinterpret_cast<glDrawTransformFeedbackStreamInstancedCallback>(OpenGLGetProcAddress("glDrawTransformFeedbackStreamInstanced"));
	glDrawTransformFeedbackStreamInstanced(mode,id,stream,instancecount);
}
glDrawTransformFeedbackStreamInstancedCallback glDrawTransformFeedbackStreamInstanced = glDrawTransformFeedbackStreamInstancedDispatcher;

void glEdgeFlagDispatcher(GLboolean flag){
	glEdgeFlag = reinterpret_cast<glEdgeFlagCallback>(OpenGLGetProcAddress("glEdgeFlag"));
	glEdgeFlag(flag);
}
glEdgeFlagCallback glEdgeFlag = glEdgeFlagDispatcher;

void glEdgeFlagPointerDispatcher(GLsizei stride,const void * pointer){
	glEdgeFlagPointer = reinterpret_cast<glEdgeFlagPointerCallback>(OpenGLGetProcAddress("glEdgeFlagPointer"));
	glEdgeFlagPointer(stride,pointer);
}
glEdgeFlagPointerCallback glEdgeFlagPointer = glEdgeFlagPointerDispatcher;

void glEdgeFlagvDispatcher(const GLboolean * flag){
	glEdgeFlagv = reinterpret_cast<glEdgeFlagvCallback>(OpenGLGetProcAddress("glEdgeFlagv"));
	glEdgeFlagv(flag);
}
glEdgeFlagvCallback glEdgeFlagv = glEdgeFlagvDispatcher;

void glEnableDispatcher(GLenum cap){
	glEnable = reinterpret_cast<glEnableCallback>(OpenGLGetProcAddress("glEnable"));
	glEnable(cap);
}
glEnableCallback glEnable = glEnableDispatcher;

void glEnableClientStateDispatcher(GLenum array){
	glEnableClientState = reinterpret_cast<glEnableClientStateCallback>(OpenGLGetProcAddress("glEnableClientState"));
	glEnableClientState(array);
}
glEnableClientStateCallback glEnableClientState = glEnableClientStateDispatcher;

void glEnableVertexArrayAttribDispatcher(GLuint vaobj,GLuint index){
	glEnableVertexArrayAttrib = reinterpret_cast<glEnableVertexArrayAttribCallback>(OpenGLGetProcAddress("glEnableVertexArrayAttrib"));
	glEnableVertexArrayAttrib(vaobj,index);
}
glEnableVertexArrayAttribCallback glEnableVertexArrayAttrib = glEnableVertexArrayAttribDispatcher;

void glEnableVertexAttribArrayDispatcher(GLuint index){
	glEnableVertexAttribArray = reinterpret_cast<glEnableVertexAttribArrayCallback>(OpenGLGetProcAddress("glEnableVertexAttribArray"));
	glEnableVertexAttribArray(index);
}
glEnableVertexAttribArrayCallback glEnableVertexAttribArray = glEnableVertexAttribArrayDispatcher;

void glEnableiDispatcher(GLenum target,GLuint index){
	glEnablei = reinterpret_cast<glEnableiCallback>(OpenGLGetProcAddress("glEnablei"));
	glEnablei(target,index);
}
glEnableiCallback glEnablei = glEnableiDispatcher;

void glEndDispatcher(){
	glEnd = reinterpret_cast<glEndCallback>(OpenGLGetProcAddress("glEnd"));
	glEnd();
}
glEndCallback glEnd = glEndDispatcher;

void glEndConditionalRenderDispatcher(){
	glEndConditionalRender = reinterpret_cast<glEndConditionalRenderCallback>(OpenGLGetProcAddress("glEndConditionalRender"));
	glEndConditionalRender();
}
glEndConditionalRenderCallback glEndConditionalRender = glEndConditionalRenderDispatcher;

void glEndListDispatcher(){
	glEndList = reinterpret_cast<glEndListCallback>(OpenGLGetProcAddress("glEndList"));
	glEndList();
}
glEndListCallback glEndList = glEndListDispatcher;

void glEndQueryDispatcher(GLenum target){
	glEndQuery = reinterpret_cast<glEndQueryCallback>(OpenGLGetProcAddress("glEndQuery"));
	glEndQuery(target);
}
glEndQueryCallback glEndQuery = glEndQueryDispatcher;

void glEndQueryIndexedDispatcher(GLenum target,GLuint index){
	glEndQueryIndexed = reinterpret_cast<glEndQueryIndexedCallback>(OpenGLGetProcAddress("glEndQueryIndexed"));
	glEndQueryIndexed(target,index);
}
glEndQueryIndexedCallback glEndQueryIndexed = glEndQueryIndexedDispatcher;

void glEndTransformFeedbackDispatcher(){
	glEndTransformFeedback = reinterpret_cast<glEndTransformFeedbackCallback>(OpenGLGetProcAddress("glEndTransformFeedback"));
	glEndTransformFeedback();
}
glEndTransformFeedbackCallback glEndTransformFeedback = glEndTransformFeedbackDispatcher;

void glEvalCoord1dDispatcher(GLdouble u){
	glEvalCoord1d = reinterpret_cast<glEvalCoord1dCallback>(OpenGLGetProcAddress("glEvalCoord1d"));
	glEvalCoord1d(u);
}
glEvalCoord1dCallback glEvalCoord1d = glEvalCoord1dDispatcher;

void glEvalCoord1dvDispatcher(const GLdouble * u){
	glEvalCoord1dv = reinterpret_cast<glEvalCoord1dvCallback>(OpenGLGetProcAddress("glEvalCoord1dv"));
	glEvalCoord1dv(u);
}
glEvalCoord1dvCallback glEvalCoord1dv = glEvalCoord1dvDispatcher;

void glEvalCoord1fDispatcher(GLfloat u){
	glEvalCoord1f = reinterpret_cast<glEvalCoord1fCallback>(OpenGLGetProcAddress("glEvalCoord1f"));
	glEvalCoord1f(u);
}
glEvalCoord1fCallback glEvalCoord1f = glEvalCoord1fDispatcher;

void glEvalCoord1fvDispatcher(const GLfloat * u){
	glEvalCoord1fv = reinterpret_cast<glEvalCoord1fvCallback>(OpenGLGetProcAddress("glEvalCoord1fv"));
	glEvalCoord1fv(u);
}
glEvalCoord1fvCallback glEvalCoord1fv = glEvalCoord1fvDispatcher;

void glEvalCoord2dDispatcher(GLdouble u,GLdouble v){
	glEvalCoord2d = reinterpret_cast<glEvalCoord2dCallback>(OpenGLGetProcAddress("glEvalCoord2d"));
	glEvalCoord2d(u,v);
}
glEvalCoord2dCallback glEvalCoord2d = glEvalCoord2dDispatcher;

void glEvalCoord2dvDispatcher(const GLdouble * u){
	glEvalCoord2dv = reinterpret_cast<glEvalCoord2dvCallback>(OpenGLGetProcAddress("glEvalCoord2dv"));
	glEvalCoord2dv(u);
}
glEvalCoord2dvCallback glEvalCoord2dv = glEvalCoord2dvDispatcher;

void glEvalCoord2fDispatcher(GLfloat u,GLfloat v){
	glEvalCoord2f = reinterpret_cast<glEvalCoord2fCallback>(OpenGLGetProcAddress("glEvalCoord2f"));
	glEvalCoord2f(u,v);
}
glEvalCoord2fCallback glEvalCoord2f = glEvalCoord2fDispatcher;

void glEvalCoord2fvDispatcher(const GLfloat * u){
	glEvalCoord2fv = reinterpret_cast<glEvalCoord2fvCallback>(OpenGLGetProcAddress("glEvalCoord2fv"));
	glEvalCoord2fv(u);
}
glEvalCoord2fvCallback glEvalCoord2fv = glEvalCoord2fvDispatcher;

void glEvalMesh1Dispatcher(GLenum mode,GLint i1,GLint i2){
	glEvalMesh1 = reinterpret_cast<glEvalMesh1Callback>(OpenGLGetProcAddress("glEvalMesh1"));
	glEvalMesh1(mode,i1,i2);
}
glEvalMesh1Callback glEvalMesh1 = glEvalMesh1Dispatcher;

void glEvalMesh2Dispatcher(GLenum mode,GLint i1,GLint i2,GLint j1,GLint j2){
	glEvalMesh2 = reinterpret_cast<glEvalMesh2Callback>(OpenGLGetProcAddress("glEvalMesh2"));
	glEvalMesh2(mode,i1,i2,j1,j2);
}
glEvalMesh2Callback glEvalMesh2 = glEvalMesh2Dispatcher;

void glEvalPoint1Dispatcher(GLint i){
	glEvalPoint1 = reinterpret_cast<glEvalPoint1Callback>(OpenGLGetProcAddress("glEvalPoint1"));
	glEvalPoint1(i);
}
glEvalPoint1Callback glEvalPoint1 = glEvalPoint1Dispatcher;

void glEvalPoint2Dispatcher(GLint i,GLint j){
	glEvalPoint2 = reinterpret_cast<glEvalPoint2Callback>(OpenGLGetProcAddress("glEvalPoint2"));
	glEvalPoint2(i,j);
}
glEvalPoint2Callback glEvalPoint2 = glEvalPoint2Dispatcher;

void glFeedbackBufferDispatcher(GLsizei size,GLenum type,GLfloat * buffer){
	glFeedbackBuffer = reinterpret_cast<glFeedbackBufferCallback>(OpenGLGetProcAddress("glFeedbackBuffer"));
	glFeedbackBuffer(size,type,buffer);
}
glFeedbackBufferCallback glFeedbackBuffer = glFeedbackBufferDispatcher;

GLsync glFenceSyncDispatcher(GLenum condition,GLbitfield flags){
	glFenceSync = reinterpret_cast<glFenceSyncCallback>(OpenGLGetProcAddress("glFenceSync"));
	return 	glFenceSync(condition,flags);
}
glFenceSyncCallback glFenceSync = glFenceSyncDispatcher;

void glFinishDispatcher(){
	glFinish = reinterpret_cast<glFinishCallback>(OpenGLGetProcAddress("glFinish"));
	glFinish();
}
glFinishCallback glFinish = glFinishDispatcher;

void glFlushDispatcher(){
	glFlush = reinterpret_cast<glFlushCallback>(OpenGLGetProcAddress("glFlush"));
	glFlush();
}
glFlushCallback glFlush = glFlushDispatcher;

void glFlushMappedBufferRangeDispatcher(GLenum target,GLintptr offset,GLsizeiptr length){
	glFlushMappedBufferRange = reinterpret_cast<glFlushMappedBufferRangeCallback>(OpenGLGetProcAddress("glFlushMappedBufferRange"));
	glFlushMappedBufferRange(target,offset,length);
}
glFlushMappedBufferRangeCallback glFlushMappedBufferRange = glFlushMappedBufferRangeDispatcher;

void glFlushMappedNamedBufferRangeDispatcher(GLuint buffer,GLintptr offset,GLsizei length){
	glFlushMappedNamedBufferRange = reinterpret_cast<glFlushMappedNamedBufferRangeCallback>(OpenGLGetProcAddress("glFlushMappedNamedBufferRange"));
	glFlushMappedNamedBufferRange(buffer,offset,length);
}
glFlushMappedNamedBufferRangeCallback glFlushMappedNamedBufferRange = glFlushMappedNamedBufferRangeDispatcher;

void glFogCoordPointerDispatcher(GLenum type,GLsizei stride,const void * pointer){
	glFogCoordPointer = reinterpret_cast<glFogCoordPointerCallback>(OpenGLGetProcAddress("glFogCoordPointer"));
	glFogCoordPointer(type,stride,pointer);
}
glFogCoordPointerCallback glFogCoordPointer = glFogCoordPointerDispatcher;

void glFogCoorddDispatcher(GLdouble coord){
	glFogCoordd = reinterpret_cast<glFogCoorddCallback>(OpenGLGetProcAddress("glFogCoordd"));
	glFogCoordd(coord);
}
glFogCoorddCallback glFogCoordd = glFogCoorddDispatcher;

void glFogCoorddvDispatcher(const GLdouble * coord){
	glFogCoorddv = reinterpret_cast<glFogCoorddvCallback>(OpenGLGetProcAddress("glFogCoorddv"));
	glFogCoorddv(coord);
}
glFogCoorddvCallback glFogCoorddv = glFogCoorddvDispatcher;

void glFogCoordfDispatcher(GLfloat coord){
	glFogCoordf = reinterpret_cast<glFogCoordfCallback>(OpenGLGetProcAddress("glFogCoordf"));
	glFogCoordf(coord);
}
glFogCoordfCallback glFogCoordf = glFogCoordfDispatcher;

void glFogCoordfvDispatcher(const GLfloat * coord){
	glFogCoordfv = reinterpret_cast<glFogCoordfvCallback>(OpenGLGetProcAddress("glFogCoordfv"));
	glFogCoordfv(coord);
}
glFogCoordfvCallback glFogCoordfv = glFogCoordfvDispatcher;

void glFogfDispatcher(GLenum pname,GLfloat param){
	glFogf = reinterpret_cast<glFogfCallback>(OpenGLGetProcAddress("glFogf"));
	glFogf(pname,param);
}
glFogfCallback glFogf = glFogfDispatcher;

void glFogfvDispatcher(GLenum pname,const GLfloat * params){
	glFogfv = reinterpret_cast<glFogfvCallback>(OpenGLGetProcAddress("glFogfv"));
	glFogfv(pname,params);
}
glFogfvCallback glFogfv = glFogfvDispatcher;

void glFogiDispatcher(GLenum pname,GLint param){
	glFogi = reinterpret_cast<glFogiCallback>(OpenGLGetProcAddress("glFogi"));
	glFogi(pname,param);
}
glFogiCallback glFogi = glFogiDispatcher;

void glFogivDispatcher(GLenum pname,const GLint * params){
	glFogiv = reinterpret_cast<glFogivCallback>(OpenGLGetProcAddress("glFogiv"));
	glFogiv(pname,params);
}
glFogivCallback glFogiv = glFogivDispatcher;

void glFramebufferParameteriDispatcher(GLenum target,GLenum pname,GLint param){
	glFramebufferParameteri = reinterpret_cast<glFramebufferParameteriCallback>(OpenGLGetProcAddress("glFramebufferParameteri"));
	glFramebufferParameteri(target,pname,param);
}
glFramebufferParameteriCallback glFramebufferParameteri = glFramebufferParameteriDispatcher;

void glFramebufferRenderbufferDispatcher(GLenum target,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer){
	glFramebufferRenderbuffer = reinterpret_cast<glFramebufferRenderbufferCallback>(OpenGLGetProcAddress("glFramebufferRenderbuffer"));
	glFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer);
}
glFramebufferRenderbufferCallback glFramebufferRenderbuffer = glFramebufferRenderbufferDispatcher;

void glFramebufferTextureDispatcher(GLenum target,GLenum attachment,GLuint texture,GLint level){
	glFramebufferTexture = reinterpret_cast<glFramebufferTextureCallback>(OpenGLGetProcAddress("glFramebufferTexture"));
	glFramebufferTexture(target,attachment,texture,level);
}
glFramebufferTextureCallback glFramebufferTexture = glFramebufferTextureDispatcher;

void glFramebufferTexture1DDispatcher(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level){
	glFramebufferTexture1D = reinterpret_cast<glFramebufferTexture1DCallback>(OpenGLGetProcAddress("glFramebufferTexture1D"));
	glFramebufferTexture1D(target,attachment,textarget,texture,level);
}
glFramebufferTexture1DCallback glFramebufferTexture1D = glFramebufferTexture1DDispatcher;

void glFramebufferTexture2DDispatcher(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level){
	glFramebufferTexture2D = reinterpret_cast<glFramebufferTexture2DCallback>(OpenGLGetProcAddress("glFramebufferTexture2D"));
	glFramebufferTexture2D(target,attachment,textarget,texture,level);
}
glFramebufferTexture2DCallback glFramebufferTexture2D = glFramebufferTexture2DDispatcher;

void glFramebufferTexture3DDispatcher(GLenum target,GLenum attachment,GLenum textarget,GLuint texture,GLint level,GLint zoffset){
	glFramebufferTexture3D = reinterpret_cast<glFramebufferTexture3DCallback>(OpenGLGetProcAddress("glFramebufferTexture3D"));
	glFramebufferTexture3D(target,attachment,textarget,texture,level,zoffset);
}
glFramebufferTexture3DCallback glFramebufferTexture3D = glFramebufferTexture3DDispatcher;

void glFramebufferTextureLayerDispatcher(GLenum target,GLenum attachment,GLuint texture,GLint level,GLint layer){
	glFramebufferTextureLayer = reinterpret_cast<glFramebufferTextureLayerCallback>(OpenGLGetProcAddress("glFramebufferTextureLayer"));
	glFramebufferTextureLayer(target,attachment,texture,level,layer);
}
glFramebufferTextureLayerCallback glFramebufferTextureLayer = glFramebufferTextureLayerDispatcher;

void glFrontFaceDispatcher(GLenum mode){
	glFrontFace = reinterpret_cast<glFrontFaceCallback>(OpenGLGetProcAddress("glFrontFace"));
	glFrontFace(mode);
}
glFrontFaceCallback glFrontFace = glFrontFaceDispatcher;

void glFrustumDispatcher(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar){
	glFrustum = reinterpret_cast<glFrustumCallback>(OpenGLGetProcAddress("glFrustum"));
	glFrustum(left,right,bottom,top,zNear,zFar);
}
glFrustumCallback glFrustum = glFrustumDispatcher;

void glGenBuffersDispatcher(GLsizei n,GLuint * buffers){
	glGenBuffers = reinterpret_cast<glGenBuffersCallback>(OpenGLGetProcAddress("glGenBuffers"));
	glGenBuffers(n,buffers);
}
glGenBuffersCallback glGenBuffers = glGenBuffersDispatcher;

void glGenFramebuffersDispatcher(GLsizei n,GLuint * framebuffers){
	glGenFramebuffers = reinterpret_cast<glGenFramebuffersCallback>(OpenGLGetProcAddress("glGenFramebuffers"));
	glGenFramebuffers(n,framebuffers);
}
glGenFramebuffersCallback glGenFramebuffers = glGenFramebuffersDispatcher;

GLuint glGenListsDispatcher(GLsizei range){
	glGenLists = reinterpret_cast<glGenListsCallback>(OpenGLGetProcAddress("glGenLists"));
	return 	glGenLists(range);
}
glGenListsCallback glGenLists = glGenListsDispatcher;

void glGenProgramPipelinesDispatcher(GLsizei n,GLuint * pipelines){
	glGenProgramPipelines = reinterpret_cast<glGenProgramPipelinesCallback>(OpenGLGetProcAddress("glGenProgramPipelines"));
	glGenProgramPipelines(n,pipelines);
}
glGenProgramPipelinesCallback glGenProgramPipelines = glGenProgramPipelinesDispatcher;

void glGenQueriesDispatcher(GLsizei n,GLuint * ids){
	glGenQueries = reinterpret_cast<glGenQueriesCallback>(OpenGLGetProcAddress("glGenQueries"));
	glGenQueries(n,ids);
}
glGenQueriesCallback glGenQueries = glGenQueriesDispatcher;

void glGenRenderbuffersDispatcher(GLsizei n,GLuint * renderbuffers){
	glGenRenderbuffers = reinterpret_cast<glGenRenderbuffersCallback>(OpenGLGetProcAddress("glGenRenderbuffers"));
	glGenRenderbuffers(n,renderbuffers);
}
glGenRenderbuffersCallback glGenRenderbuffers = glGenRenderbuffersDispatcher;

void glGenSamplersDispatcher(GLsizei count,GLuint * samplers){
	glGenSamplers = reinterpret_cast<glGenSamplersCallback>(OpenGLGetProcAddress("glGenSamplers"));
	glGenSamplers(count,samplers);
}
glGenSamplersCallback glGenSamplers = glGenSamplersDispatcher;

void glGenTexturesDispatcher(GLsizei n,GLuint * textures){
	glGenTextures = reinterpret_cast<glGenTexturesCallback>(OpenGLGetProcAddress("glGenTextures"));
	glGenTextures(n,textures);
}
glGenTexturesCallback glGenTextures = glGenTexturesDispatcher;

void glGenTransformFeedbacksDispatcher(GLsizei n,GLuint * ids){
	glGenTransformFeedbacks = reinterpret_cast<glGenTransformFeedbacksCallback>(OpenGLGetProcAddress("glGenTransformFeedbacks"));
	glGenTransformFeedbacks(n,ids);
}
glGenTransformFeedbacksCallback glGenTransformFeedbacks = glGenTransformFeedbacksDispatcher;

void glGenVertexArraysDispatcher(GLsizei n,GLuint * arrays){
	glGenVertexArrays = reinterpret_cast<glGenVertexArraysCallback>(OpenGLGetProcAddress("glGenVertexArrays"));
	glGenVertexArrays(n,arrays);
}
glGenVertexArraysCallback glGenVertexArrays = glGenVertexArraysDispatcher;

void glGenerateMipmapDispatcher(GLenum target){
	glGenerateMipmap = reinterpret_cast<glGenerateMipmapCallback>(OpenGLGetProcAddress("glGenerateMipmap"));
	glGenerateMipmap(target);
}
glGenerateMipmapCallback glGenerateMipmap = glGenerateMipmapDispatcher;

void glGenerateTextureMipmapDispatcher(GLuint texture){
	glGenerateTextureMipmap = reinterpret_cast<glGenerateTextureMipmapCallback>(OpenGLGetProcAddress("glGenerateTextureMipmap"));
	glGenerateTextureMipmap(texture);
}
glGenerateTextureMipmapCallback glGenerateTextureMipmap = glGenerateTextureMipmapDispatcher;

void glGetActiveAtomicCounterBufferivDispatcher(GLuint program,GLuint bufferIndex,GLenum pname,GLint * params){
	glGetActiveAtomicCounterBufferiv = reinterpret_cast<glGetActiveAtomicCounterBufferivCallback>(OpenGLGetProcAddress("glGetActiveAtomicCounterBufferiv"));
	glGetActiveAtomicCounterBufferiv(program,bufferIndex,pname,params);
}
glGetActiveAtomicCounterBufferivCallback glGetActiveAtomicCounterBufferiv = glGetActiveAtomicCounterBufferivDispatcher;

void glGetActiveAttribDispatcher(GLuint program,GLuint index,GLsizei bufSize,GLsizei * length,GLint * size,GLenum * type,GLchar * name){
	glGetActiveAttrib = reinterpret_cast<glGetActiveAttribCallback>(OpenGLGetProcAddress("glGetActiveAttrib"));
	glGetActiveAttrib(program,index,bufSize,length,size,type,name);
}
glGetActiveAttribCallback glGetActiveAttrib = glGetActiveAttribDispatcher;

void glGetActiveSubroutineNameDispatcher(GLuint program,GLenum shadertype,GLuint index,GLsizei bufsize,GLsizei * length,GLchar * name){
	glGetActiveSubroutineName = reinterpret_cast<glGetActiveSubroutineNameCallback>(OpenGLGetProcAddress("glGetActiveSubroutineName"));
	glGetActiveSubroutineName(program,shadertype,index,bufsize,length,name);
}
glGetActiveSubroutineNameCallback glGetActiveSubroutineName = glGetActiveSubroutineNameDispatcher;

void glGetActiveSubroutineUniformNameDispatcher(GLuint program,GLenum shadertype,GLuint index,GLsizei bufsize,GLsizei * length,GLchar * name){
	glGetActiveSubroutineUniformName = reinterpret_cast<glGetActiveSubroutineUniformNameCallback>(OpenGLGetProcAddress("glGetActiveSubroutineUniformName"));
	glGetActiveSubroutineUniformName(program,shadertype,index,bufsize,length,name);
}
glGetActiveSubroutineUniformNameCallback glGetActiveSubroutineUniformName = glGetActiveSubroutineUniformNameDispatcher;

void glGetActiveSubroutineUniformivDispatcher(GLuint program,GLenum shadertype,GLuint index,GLenum pname,GLint * values){
	glGetActiveSubroutineUniformiv = reinterpret_cast<glGetActiveSubroutineUniformivCallback>(OpenGLGetProcAddress("glGetActiveSubroutineUniformiv"));
	glGetActiveSubroutineUniformiv(program,shadertype,index,pname,values);
}
glGetActiveSubroutineUniformivCallback glGetActiveSubroutineUniformiv = glGetActiveSubroutineUniformivDispatcher;

void glGetActiveUniformDispatcher(GLuint program,GLuint index,GLsizei bufSize,GLsizei * length,GLint * size,GLenum * type,GLchar * name){
	glGetActiveUniform = reinterpret_cast<glGetActiveUniformCallback>(OpenGLGetProcAddress("glGetActiveUniform"));
	glGetActiveUniform(program,index,bufSize,length,size,type,name);
}
glGetActiveUniformCallback glGetActiveUniform = glGetActiveUniformDispatcher;

void glGetActiveUniformBlockNameDispatcher(GLuint program,GLuint uniformBlockIndex,GLsizei bufSize,GLsizei * length,GLchar * uniformBlockName){
	glGetActiveUniformBlockName = reinterpret_cast<glGetActiveUniformBlockNameCallback>(OpenGLGetProcAddress("glGetActiveUniformBlockName"));
	glGetActiveUniformBlockName(program,uniformBlockIndex,bufSize,length,uniformBlockName);
}
glGetActiveUniformBlockNameCallback glGetActiveUniformBlockName = glGetActiveUniformBlockNameDispatcher;

void glGetActiveUniformBlockivDispatcher(GLuint program,GLuint uniformBlockIndex,GLenum pname,GLint * params){
	glGetActiveUniformBlockiv = reinterpret_cast<glGetActiveUniformBlockivCallback>(OpenGLGetProcAddress("glGetActiveUniformBlockiv"));
	glGetActiveUniformBlockiv(program,uniformBlockIndex,pname,params);
}
glGetActiveUniformBlockivCallback glGetActiveUniformBlockiv = glGetActiveUniformBlockivDispatcher;

void glGetActiveUniformNameDispatcher(GLuint program,GLuint uniformIndex,GLsizei bufSize,GLsizei * length,GLchar * uniformName){
	glGetActiveUniformName = reinterpret_cast<glGetActiveUniformNameCallback>(OpenGLGetProcAddress("glGetActiveUniformName"));
	glGetActiveUniformName(program,uniformIndex,bufSize,length,uniformName);
}
glGetActiveUniformNameCallback glGetActiveUniformName = glGetActiveUniformNameDispatcher;

void glGetActiveUniformsivDispatcher(GLuint program,GLsizei uniformCount,const GLuint * uniformIndices,GLenum pname,GLint * params){
	glGetActiveUniformsiv = reinterpret_cast<glGetActiveUniformsivCallback>(OpenGLGetProcAddress("glGetActiveUniformsiv"));
	glGetActiveUniformsiv(program,uniformCount,uniformIndices,pname,params);
}
glGetActiveUniformsivCallback glGetActiveUniformsiv = glGetActiveUniformsivDispatcher;

void glGetAttachedShadersDispatcher(GLuint program,GLsizei maxCount,GLsizei * count,GLuint * shaders){
	glGetAttachedShaders = reinterpret_cast<glGetAttachedShadersCallback>(OpenGLGetProcAddress("glGetAttachedShaders"));
	glGetAttachedShaders(program,maxCount,count,shaders);
}
glGetAttachedShadersCallback glGetAttachedShaders = glGetAttachedShadersDispatcher;

GLint glGetAttribLocationDispatcher(GLuint program,const GLchar * name){
	glGetAttribLocation = reinterpret_cast<glGetAttribLocationCallback>(OpenGLGetProcAddress("glGetAttribLocation"));
	return 	glGetAttribLocation(program,name);
}
glGetAttribLocationCallback glGetAttribLocation = glGetAttribLocationDispatcher;

void glGetBooleani_vDispatcher(GLenum target,GLuint index,GLboolean * data){
	glGetBooleani_v = reinterpret_cast<glGetBooleani_vCallback>(OpenGLGetProcAddress("glGetBooleani_v"));
	glGetBooleani_v(target,index,data);
}
glGetBooleani_vCallback glGetBooleani_v = glGetBooleani_vDispatcher;

void glGetBooleanvDispatcher(GLenum pname,GLboolean * data){
	glGetBooleanv = reinterpret_cast<glGetBooleanvCallback>(OpenGLGetProcAddress("glGetBooleanv"));
	glGetBooleanv(pname,data);
}
glGetBooleanvCallback glGetBooleanv = glGetBooleanvDispatcher;

void glGetBufferParameteri64vDispatcher(GLenum target,GLenum pname,GLint64 * params){
	glGetBufferParameteri64v = reinterpret_cast<glGetBufferParameteri64vCallback>(OpenGLGetProcAddress("glGetBufferParameteri64v"));
	glGetBufferParameteri64v(target,pname,params);
}
glGetBufferParameteri64vCallback glGetBufferParameteri64v = glGetBufferParameteri64vDispatcher;

void glGetBufferParameterivDispatcher(GLenum target,GLenum pname,GLint * params){
	glGetBufferParameteriv = reinterpret_cast<glGetBufferParameterivCallback>(OpenGLGetProcAddress("glGetBufferParameteriv"));
	glGetBufferParameteriv(target,pname,params);
}
glGetBufferParameterivCallback glGetBufferParameteriv = glGetBufferParameterivDispatcher;

void glGetBufferPointervDispatcher(GLenum target,GLenum pname,void ** params){
	glGetBufferPointerv = reinterpret_cast<glGetBufferPointervCallback>(OpenGLGetProcAddress("glGetBufferPointerv"));
	glGetBufferPointerv(target,pname,params);
}
glGetBufferPointervCallback glGetBufferPointerv = glGetBufferPointervDispatcher;

void glGetBufferSubDataDispatcher(GLenum target,GLintptr offset,GLsizeiptr size,void * data){
	glGetBufferSubData = reinterpret_cast<glGetBufferSubDataCallback>(OpenGLGetProcAddress("glGetBufferSubData"));
	glGetBufferSubData(target,offset,size,data);
}
glGetBufferSubDataCallback glGetBufferSubData = glGetBufferSubDataDispatcher;

void glGetClipPlaneDispatcher(GLenum plane,GLdouble * equation){
	glGetClipPlane = reinterpret_cast<glGetClipPlaneCallback>(OpenGLGetProcAddress("glGetClipPlane"));
	glGetClipPlane(plane,equation);
}
glGetClipPlaneCallback glGetClipPlane = glGetClipPlaneDispatcher;

void glGetCompressedTexImageDispatcher(GLenum target,GLint level,void * img){
	glGetCompressedTexImage = reinterpret_cast<glGetCompressedTexImageCallback>(OpenGLGetProcAddress("glGetCompressedTexImage"));
	glGetCompressedTexImage(target,level,img);
}
glGetCompressedTexImageCallback glGetCompressedTexImage = glGetCompressedTexImageDispatcher;

void glGetCompressedTextureImageDispatcher(GLuint texture,GLint level,GLsizei bufSize,void * pixels){
	glGetCompressedTextureImage = reinterpret_cast<glGetCompressedTextureImageCallback>(OpenGLGetProcAddress("glGetCompressedTextureImage"));
	glGetCompressedTextureImage(texture,level,bufSize,pixels);
}
glGetCompressedTextureImageCallback glGetCompressedTextureImage = glGetCompressedTextureImageDispatcher;

void glGetCompressedTextureSubImageDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLsizei bufSize,void * pixels){
	glGetCompressedTextureSubImage = reinterpret_cast<glGetCompressedTextureSubImageCallback>(OpenGLGetProcAddress("glGetCompressedTextureSubImage"));
	glGetCompressedTextureSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,bufSize,pixels);
}
glGetCompressedTextureSubImageCallback glGetCompressedTextureSubImage = glGetCompressedTextureSubImageDispatcher;

GLuint glGetDebugMessageLogDispatcher(GLuint count,GLsizei bufSize,GLenum * sources,GLenum * types,GLuint * ids,GLenum * severities,GLsizei * lengths,GLchar * messageLog){
	glGetDebugMessageLog = reinterpret_cast<glGetDebugMessageLogCallback>(OpenGLGetProcAddress("glGetDebugMessageLog"));
	return 	glGetDebugMessageLog(count,bufSize,sources,types,ids,severities,lengths,messageLog);
}
glGetDebugMessageLogCallback glGetDebugMessageLog = glGetDebugMessageLogDispatcher;

void glGetDoublei_vDispatcher(GLenum target,GLuint index,GLdouble * data){
	glGetDoublei_v = reinterpret_cast<glGetDoublei_vCallback>(OpenGLGetProcAddress("glGetDoublei_v"));
	glGetDoublei_v(target,index,data);
}
glGetDoublei_vCallback glGetDoublei_v = glGetDoublei_vDispatcher;

void glGetDoublevDispatcher(GLenum pname,GLdouble * data){
	glGetDoublev = reinterpret_cast<glGetDoublevCallback>(OpenGLGetProcAddress("glGetDoublev"));
	glGetDoublev(pname,data);
}
glGetDoublevCallback glGetDoublev = glGetDoublevDispatcher;

GLenum glGetErrorDispatcher(){
	glGetError = reinterpret_cast<glGetErrorCallback>(OpenGLGetProcAddress("glGetError"));
	return 	glGetError();
}
glGetErrorCallback glGetError = glGetErrorDispatcher;

void glGetFloati_vDispatcher(GLenum target,GLuint index,GLfloat * data){
	glGetFloati_v = reinterpret_cast<glGetFloati_vCallback>(OpenGLGetProcAddress("glGetFloati_v"));
	glGetFloati_v(target,index,data);
}
glGetFloati_vCallback glGetFloati_v = glGetFloati_vDispatcher;

void glGetFloatvDispatcher(GLenum pname,GLfloat * data){
	glGetFloatv = reinterpret_cast<glGetFloatvCallback>(OpenGLGetProcAddress("glGetFloatv"));
	glGetFloatv(pname,data);
}
glGetFloatvCallback glGetFloatv = glGetFloatvDispatcher;

GLint glGetFragDataIndexDispatcher(GLuint program,const GLchar * name){
	glGetFragDataIndex = reinterpret_cast<glGetFragDataIndexCallback>(OpenGLGetProcAddress("glGetFragDataIndex"));
	return 	glGetFragDataIndex(program,name);
}
glGetFragDataIndexCallback glGetFragDataIndex = glGetFragDataIndexDispatcher;

GLint glGetFragDataLocationDispatcher(GLuint program,const GLchar * name){
	glGetFragDataLocation = reinterpret_cast<glGetFragDataLocationCallback>(OpenGLGetProcAddress("glGetFragDataLocation"));
	return 	glGetFragDataLocation(program,name);
}
glGetFragDataLocationCallback glGetFragDataLocation = glGetFragDataLocationDispatcher;

void glGetFramebufferAttachmentParameterivDispatcher(GLenum target,GLenum attachment,GLenum pname,GLint * params){
	glGetFramebufferAttachmentParameteriv = reinterpret_cast<glGetFramebufferAttachmentParameterivCallback>(OpenGLGetProcAddress("glGetFramebufferAttachmentParameteriv"));
	glGetFramebufferAttachmentParameteriv(target,attachment,pname,params);
}
glGetFramebufferAttachmentParameterivCallback glGetFramebufferAttachmentParameteriv = glGetFramebufferAttachmentParameterivDispatcher;

void glGetFramebufferParameterivDispatcher(GLenum target,GLenum pname,GLint * params){
	glGetFramebufferParameteriv = reinterpret_cast<glGetFramebufferParameterivCallback>(OpenGLGetProcAddress("glGetFramebufferParameteriv"));
	glGetFramebufferParameteriv(target,pname,params);
}
glGetFramebufferParameterivCallback glGetFramebufferParameteriv = glGetFramebufferParameterivDispatcher;

GLenum glGetGraphicsResetStatusDispatcher(){
	glGetGraphicsResetStatus = reinterpret_cast<glGetGraphicsResetStatusCallback>(OpenGLGetProcAddress("glGetGraphicsResetStatus"));
	return 	glGetGraphicsResetStatus();
}
glGetGraphicsResetStatusCallback glGetGraphicsResetStatus = glGetGraphicsResetStatusDispatcher;

void glGetInteger64i_vDispatcher(GLenum target,GLuint index,GLint64 * data){
	glGetInteger64i_v = reinterpret_cast<glGetInteger64i_vCallback>(OpenGLGetProcAddress("glGetInteger64i_v"));
	glGetInteger64i_v(target,index,data);
}
glGetInteger64i_vCallback glGetInteger64i_v = glGetInteger64i_vDispatcher;

void glGetInteger64vDispatcher(GLenum pname,GLint64 * data){
	glGetInteger64v = reinterpret_cast<glGetInteger64vCallback>(OpenGLGetProcAddress("glGetInteger64v"));
	glGetInteger64v(pname,data);
}
glGetInteger64vCallback glGetInteger64v = glGetInteger64vDispatcher;

void glGetIntegeri_vDispatcher(GLenum target,GLuint index,GLint * data){
	glGetIntegeri_v = reinterpret_cast<glGetIntegeri_vCallback>(OpenGLGetProcAddress("glGetIntegeri_v"));
	glGetIntegeri_v(target,index,data);
}
glGetIntegeri_vCallback glGetIntegeri_v = glGetIntegeri_vDispatcher;

void glGetIntegervDispatcher(GLenum pname,GLint * data){
	glGetIntegerv = reinterpret_cast<glGetIntegervCallback>(OpenGLGetProcAddress("glGetIntegerv"));
	glGetIntegerv(pname,data);
}
glGetIntegervCallback glGetIntegerv = glGetIntegervDispatcher;

void glGetInternalformati64vDispatcher(GLenum target,GLenum internalformat,GLenum pname,GLsizei bufSize,GLint64 * params){
	glGetInternalformati64v = reinterpret_cast<glGetInternalformati64vCallback>(OpenGLGetProcAddress("glGetInternalformati64v"));
	glGetInternalformati64v(target,internalformat,pname,bufSize,params);
}
glGetInternalformati64vCallback glGetInternalformati64v = glGetInternalformati64vDispatcher;

void glGetInternalformativDispatcher(GLenum target,GLenum internalformat,GLenum pname,GLsizei bufSize,GLint * params){
	glGetInternalformativ = reinterpret_cast<glGetInternalformativCallback>(OpenGLGetProcAddress("glGetInternalformativ"));
	glGetInternalformativ(target,internalformat,pname,bufSize,params);
}
glGetInternalformativCallback glGetInternalformativ = glGetInternalformativDispatcher;

void glGetLightfvDispatcher(GLenum light,GLenum pname,GLfloat * params){
	glGetLightfv = reinterpret_cast<glGetLightfvCallback>(OpenGLGetProcAddress("glGetLightfv"));
	glGetLightfv(light,pname,params);
}
glGetLightfvCallback glGetLightfv = glGetLightfvDispatcher;

void glGetLightivDispatcher(GLenum light,GLenum pname,GLint * params){
	glGetLightiv = reinterpret_cast<glGetLightivCallback>(OpenGLGetProcAddress("glGetLightiv"));
	glGetLightiv(light,pname,params);
}
glGetLightivCallback glGetLightiv = glGetLightivDispatcher;

void glGetMapdvDispatcher(GLenum target,GLenum query,GLdouble * v){
	glGetMapdv = reinterpret_cast<glGetMapdvCallback>(OpenGLGetProcAddress("glGetMapdv"));
	glGetMapdv(target,query,v);
}
glGetMapdvCallback glGetMapdv = glGetMapdvDispatcher;

void glGetMapfvDispatcher(GLenum target,GLenum query,GLfloat * v){
	glGetMapfv = reinterpret_cast<glGetMapfvCallback>(OpenGLGetProcAddress("glGetMapfv"));
	glGetMapfv(target,query,v);
}
glGetMapfvCallback glGetMapfv = glGetMapfvDispatcher;

void glGetMapivDispatcher(GLenum target,GLenum query,GLint * v){
	glGetMapiv = reinterpret_cast<glGetMapivCallback>(OpenGLGetProcAddress("glGetMapiv"));
	glGetMapiv(target,query,v);
}
glGetMapivCallback glGetMapiv = glGetMapivDispatcher;

void glGetMaterialfvDispatcher(GLenum face,GLenum pname,GLfloat * params){
	glGetMaterialfv = reinterpret_cast<glGetMaterialfvCallback>(OpenGLGetProcAddress("glGetMaterialfv"));
	glGetMaterialfv(face,pname,params);
}
glGetMaterialfvCallback glGetMaterialfv = glGetMaterialfvDispatcher;

void glGetMaterialivDispatcher(GLenum face,GLenum pname,GLint * params){
	glGetMaterialiv = reinterpret_cast<glGetMaterialivCallback>(OpenGLGetProcAddress("glGetMaterialiv"));
	glGetMaterialiv(face,pname,params);
}
glGetMaterialivCallback glGetMaterialiv = glGetMaterialivDispatcher;

void glGetMultisamplefvDispatcher(GLenum pname,GLuint index,GLfloat * val){
	glGetMultisamplefv = reinterpret_cast<glGetMultisamplefvCallback>(OpenGLGetProcAddress("glGetMultisamplefv"));
	glGetMultisamplefv(pname,index,val);
}
glGetMultisamplefvCallback glGetMultisamplefv = glGetMultisamplefvDispatcher;

void glGetNamedBufferParameteri64vDispatcher(GLuint buffer,GLenum pname,GLint64 * params){
	glGetNamedBufferParameteri64v = reinterpret_cast<glGetNamedBufferParameteri64vCallback>(OpenGLGetProcAddress("glGetNamedBufferParameteri64v"));
	glGetNamedBufferParameteri64v(buffer,pname,params);
}
glGetNamedBufferParameteri64vCallback glGetNamedBufferParameteri64v = glGetNamedBufferParameteri64vDispatcher;

void glGetNamedBufferParameterivDispatcher(GLuint buffer,GLenum pname,GLint * params){
	glGetNamedBufferParameteriv = reinterpret_cast<glGetNamedBufferParameterivCallback>(OpenGLGetProcAddress("glGetNamedBufferParameteriv"));
	glGetNamedBufferParameteriv(buffer,pname,params);
}
glGetNamedBufferParameterivCallback glGetNamedBufferParameteriv = glGetNamedBufferParameterivDispatcher;

void glGetNamedBufferPointervDispatcher(GLuint buffer,GLenum pname,void ** params){
	glGetNamedBufferPointerv = reinterpret_cast<glGetNamedBufferPointervCallback>(OpenGLGetProcAddress("glGetNamedBufferPointerv"));
	glGetNamedBufferPointerv(buffer,pname,params);
}
glGetNamedBufferPointervCallback glGetNamedBufferPointerv = glGetNamedBufferPointervDispatcher;

void glGetNamedBufferSubDataDispatcher(GLuint buffer,GLintptr offset,GLsizei size,void * data){
	glGetNamedBufferSubData = reinterpret_cast<glGetNamedBufferSubDataCallback>(OpenGLGetProcAddress("glGetNamedBufferSubData"));
	glGetNamedBufferSubData(buffer,offset,size,data);
}
glGetNamedBufferSubDataCallback glGetNamedBufferSubData = glGetNamedBufferSubDataDispatcher;

void glGetNamedFramebufferAttachmentParameterivDispatcher(GLuint framebuffer,GLenum attachment,GLenum pname,GLint * params){
	glGetNamedFramebufferAttachmentParameteriv = reinterpret_cast<glGetNamedFramebufferAttachmentParameterivCallback>(OpenGLGetProcAddress("glGetNamedFramebufferAttachmentParameteriv"));
	glGetNamedFramebufferAttachmentParameteriv(framebuffer,attachment,pname,params);
}
glGetNamedFramebufferAttachmentParameterivCallback glGetNamedFramebufferAttachmentParameteriv = glGetNamedFramebufferAttachmentParameterivDispatcher;

void glGetNamedFramebufferParameterivDispatcher(GLuint framebuffer,GLenum pname,GLint * param){
	glGetNamedFramebufferParameteriv = reinterpret_cast<glGetNamedFramebufferParameterivCallback>(OpenGLGetProcAddress("glGetNamedFramebufferParameteriv"));
	glGetNamedFramebufferParameteriv(framebuffer,pname,param);
}
glGetNamedFramebufferParameterivCallback glGetNamedFramebufferParameteriv = glGetNamedFramebufferParameterivDispatcher;

void glGetNamedRenderbufferParameterivDispatcher(GLuint renderbuffer,GLenum pname,GLint * params){
	glGetNamedRenderbufferParameteriv = reinterpret_cast<glGetNamedRenderbufferParameterivCallback>(OpenGLGetProcAddress("glGetNamedRenderbufferParameteriv"));
	glGetNamedRenderbufferParameteriv(renderbuffer,pname,params);
}
glGetNamedRenderbufferParameterivCallback glGetNamedRenderbufferParameteriv = glGetNamedRenderbufferParameterivDispatcher;

void glGetObjectLabelDispatcher(GLenum identifier,GLuint name,GLsizei bufSize,GLsizei * length,GLchar * label){
	glGetObjectLabel = reinterpret_cast<glGetObjectLabelCallback>(OpenGLGetProcAddress("glGetObjectLabel"));
	glGetObjectLabel(identifier,name,bufSize,length,label);
}
glGetObjectLabelCallback glGetObjectLabel = glGetObjectLabelDispatcher;

void glGetObjectPtrLabelDispatcher(const void * ptr,GLsizei bufSize,GLsizei * length,GLchar * label){
	glGetObjectPtrLabel = reinterpret_cast<glGetObjectPtrLabelCallback>(OpenGLGetProcAddress("glGetObjectPtrLabel"));
	glGetObjectPtrLabel(ptr,bufSize,length,label);
}
glGetObjectPtrLabelCallback glGetObjectPtrLabel = glGetObjectPtrLabelDispatcher;

void glGetPixelMapfvDispatcher(GLenum map,GLfloat * values){
	glGetPixelMapfv = reinterpret_cast<glGetPixelMapfvCallback>(OpenGLGetProcAddress("glGetPixelMapfv"));
	glGetPixelMapfv(map,values);
}
glGetPixelMapfvCallback glGetPixelMapfv = glGetPixelMapfvDispatcher;

void glGetPixelMapuivDispatcher(GLenum map,GLuint * values){
	glGetPixelMapuiv = reinterpret_cast<glGetPixelMapuivCallback>(OpenGLGetProcAddress("glGetPixelMapuiv"));
	glGetPixelMapuiv(map,values);
}
glGetPixelMapuivCallback glGetPixelMapuiv = glGetPixelMapuivDispatcher;

void glGetPixelMapusvDispatcher(GLenum map,GLushort * values){
	glGetPixelMapusv = reinterpret_cast<glGetPixelMapusvCallback>(OpenGLGetProcAddress("glGetPixelMapusv"));
	glGetPixelMapusv(map,values);
}
glGetPixelMapusvCallback glGetPixelMapusv = glGetPixelMapusvDispatcher;

void glGetPointervDispatcher(GLenum pname,void ** params){
	glGetPointerv = reinterpret_cast<glGetPointervCallback>(OpenGLGetProcAddress("glGetPointerv"));
	glGetPointerv(pname,params);
}
glGetPointervCallback glGetPointerv = glGetPointervDispatcher;

void glGetPolygonStippleDispatcher(GLubyte * mask){
	glGetPolygonStipple = reinterpret_cast<glGetPolygonStippleCallback>(OpenGLGetProcAddress("glGetPolygonStipple"));
	glGetPolygonStipple(mask);
}
glGetPolygonStippleCallback glGetPolygonStipple = glGetPolygonStippleDispatcher;

void glGetProgramBinaryDispatcher(GLuint program,GLsizei bufSize,GLsizei * length,GLenum * binaryFormat,void * binary){
	glGetProgramBinary = reinterpret_cast<glGetProgramBinaryCallback>(OpenGLGetProcAddress("glGetProgramBinary"));
	glGetProgramBinary(program,bufSize,length,binaryFormat,binary);
}
glGetProgramBinaryCallback glGetProgramBinary = glGetProgramBinaryDispatcher;

void glGetProgramInfoLogDispatcher(GLuint program,GLsizei bufSize,GLsizei * length,GLchar * infoLog){
	glGetProgramInfoLog = reinterpret_cast<glGetProgramInfoLogCallback>(OpenGLGetProcAddress("glGetProgramInfoLog"));
	glGetProgramInfoLog(program,bufSize,length,infoLog);
}
glGetProgramInfoLogCallback glGetProgramInfoLog = glGetProgramInfoLogDispatcher;

void glGetProgramInterfaceivDispatcher(GLuint program,GLenum programInterface,GLenum pname,GLint * params){
	glGetProgramInterfaceiv = reinterpret_cast<glGetProgramInterfaceivCallback>(OpenGLGetProcAddress("glGetProgramInterfaceiv"));
	glGetProgramInterfaceiv(program,programInterface,pname,params);
}
glGetProgramInterfaceivCallback glGetProgramInterfaceiv = glGetProgramInterfaceivDispatcher;

void glGetProgramPipelineInfoLogDispatcher(GLuint pipeline,GLsizei bufSize,GLsizei * length,GLchar * infoLog){
	glGetProgramPipelineInfoLog = reinterpret_cast<glGetProgramPipelineInfoLogCallback>(OpenGLGetProcAddress("glGetProgramPipelineInfoLog"));
	glGetProgramPipelineInfoLog(pipeline,bufSize,length,infoLog);
}
glGetProgramPipelineInfoLogCallback glGetProgramPipelineInfoLog = glGetProgramPipelineInfoLogDispatcher;

void glGetProgramPipelineivDispatcher(GLuint pipeline,GLenum pname,GLint * params){
	glGetProgramPipelineiv = reinterpret_cast<glGetProgramPipelineivCallback>(OpenGLGetProcAddress("glGetProgramPipelineiv"));
	glGetProgramPipelineiv(pipeline,pname,params);
}
glGetProgramPipelineivCallback glGetProgramPipelineiv = glGetProgramPipelineivDispatcher;

GLuint glGetProgramResourceIndexDispatcher(GLuint program,GLenum programInterface,const GLchar * name){
	glGetProgramResourceIndex = reinterpret_cast<glGetProgramResourceIndexCallback>(OpenGLGetProcAddress("glGetProgramResourceIndex"));
	return 	glGetProgramResourceIndex(program,programInterface,name);
}
glGetProgramResourceIndexCallback glGetProgramResourceIndex = glGetProgramResourceIndexDispatcher;

GLint glGetProgramResourceLocationDispatcher(GLuint program,GLenum programInterface,const GLchar * name){
	glGetProgramResourceLocation = reinterpret_cast<glGetProgramResourceLocationCallback>(OpenGLGetProcAddress("glGetProgramResourceLocation"));
	return 	glGetProgramResourceLocation(program,programInterface,name);
}
glGetProgramResourceLocationCallback glGetProgramResourceLocation = glGetProgramResourceLocationDispatcher;

GLint glGetProgramResourceLocationIndexDispatcher(GLuint program,GLenum programInterface,const GLchar * name){
	glGetProgramResourceLocationIndex = reinterpret_cast<glGetProgramResourceLocationIndexCallback>(OpenGLGetProcAddress("glGetProgramResourceLocationIndex"));
	return 	glGetProgramResourceLocationIndex(program,programInterface,name);
}
glGetProgramResourceLocationIndexCallback glGetProgramResourceLocationIndex = glGetProgramResourceLocationIndexDispatcher;

void glGetProgramResourceNameDispatcher(GLuint program,GLenum programInterface,GLuint index,GLsizei bufSize,GLsizei * length,GLchar * name){
	glGetProgramResourceName = reinterpret_cast<glGetProgramResourceNameCallback>(OpenGLGetProcAddress("glGetProgramResourceName"));
	glGetProgramResourceName(program,programInterface,index,bufSize,length,name);
}
glGetProgramResourceNameCallback glGetProgramResourceName = glGetProgramResourceNameDispatcher;

void glGetProgramResourceivDispatcher(GLuint program,GLenum programInterface,GLuint index,GLsizei propCount,const GLenum * props,GLsizei bufSize,GLsizei * length,GLint * params){
	glGetProgramResourceiv = reinterpret_cast<glGetProgramResourceivCallback>(OpenGLGetProcAddress("glGetProgramResourceiv"));
	glGetProgramResourceiv(program,programInterface,index,propCount,props,bufSize,length,params);
}
glGetProgramResourceivCallback glGetProgramResourceiv = glGetProgramResourceivDispatcher;

void glGetProgramStageivDispatcher(GLuint program,GLenum shadertype,GLenum pname,GLint * values){
	glGetProgramStageiv = reinterpret_cast<glGetProgramStageivCallback>(OpenGLGetProcAddress("glGetProgramStageiv"));
	glGetProgramStageiv(program,shadertype,pname,values);
}
glGetProgramStageivCallback glGetProgramStageiv = glGetProgramStageivDispatcher;

void glGetProgramivDispatcher(GLuint program,GLenum pname,GLint * params){
	glGetProgramiv = reinterpret_cast<glGetProgramivCallback>(OpenGLGetProcAddress("glGetProgramiv"));
	glGetProgramiv(program,pname,params);
}
glGetProgramivCallback glGetProgramiv = glGetProgramivDispatcher;

void glGetQueryIndexedivDispatcher(GLenum target,GLuint index,GLenum pname,GLint * params){
	glGetQueryIndexediv = reinterpret_cast<glGetQueryIndexedivCallback>(OpenGLGetProcAddress("glGetQueryIndexediv"));
	glGetQueryIndexediv(target,index,pname,params);
}
glGetQueryIndexedivCallback glGetQueryIndexediv = glGetQueryIndexedivDispatcher;

void glGetQueryObjecti64vDispatcher(GLuint id,GLenum pname,GLint64 * params){
	glGetQueryObjecti64v = reinterpret_cast<glGetQueryObjecti64vCallback>(OpenGLGetProcAddress("glGetQueryObjecti64v"));
	glGetQueryObjecti64v(id,pname,params);
}
glGetQueryObjecti64vCallback glGetQueryObjecti64v = glGetQueryObjecti64vDispatcher;

void glGetQueryObjectivDispatcher(GLuint id,GLenum pname,GLint * params){
	glGetQueryObjectiv = reinterpret_cast<glGetQueryObjectivCallback>(OpenGLGetProcAddress("glGetQueryObjectiv"));
	glGetQueryObjectiv(id,pname,params);
}
glGetQueryObjectivCallback glGetQueryObjectiv = glGetQueryObjectivDispatcher;

void glGetQueryObjectui64vDispatcher(GLuint id,GLenum pname,GLuint64 * params){
	glGetQueryObjectui64v = reinterpret_cast<glGetQueryObjectui64vCallback>(OpenGLGetProcAddress("glGetQueryObjectui64v"));
	glGetQueryObjectui64v(id,pname,params);
}
glGetQueryObjectui64vCallback glGetQueryObjectui64v = glGetQueryObjectui64vDispatcher;

void glGetQueryObjectuivDispatcher(GLuint id,GLenum pname,GLuint * params){
	glGetQueryObjectuiv = reinterpret_cast<glGetQueryObjectuivCallback>(OpenGLGetProcAddress("glGetQueryObjectuiv"));
	glGetQueryObjectuiv(id,pname,params);
}
glGetQueryObjectuivCallback glGetQueryObjectuiv = glGetQueryObjectuivDispatcher;

void glGetQueryivDispatcher(GLenum target,GLenum pname,GLint * params){
	glGetQueryiv = reinterpret_cast<glGetQueryivCallback>(OpenGLGetProcAddress("glGetQueryiv"));
	glGetQueryiv(target,pname,params);
}
glGetQueryivCallback glGetQueryiv = glGetQueryivDispatcher;

void glGetRenderbufferParameterivDispatcher(GLenum target,GLenum pname,GLint * params){
	glGetRenderbufferParameteriv = reinterpret_cast<glGetRenderbufferParameterivCallback>(OpenGLGetProcAddress("glGetRenderbufferParameteriv"));
	glGetRenderbufferParameteriv(target,pname,params);
}
glGetRenderbufferParameterivCallback glGetRenderbufferParameteriv = glGetRenderbufferParameterivDispatcher;

void glGetSamplerParameterIivDispatcher(GLuint sampler,GLenum pname,GLint * params){
	glGetSamplerParameterIiv = reinterpret_cast<glGetSamplerParameterIivCallback>(OpenGLGetProcAddress("glGetSamplerParameterIiv"));
	glGetSamplerParameterIiv(sampler,pname,params);
}
glGetSamplerParameterIivCallback glGetSamplerParameterIiv = glGetSamplerParameterIivDispatcher;

void glGetSamplerParameterIuivDispatcher(GLuint sampler,GLenum pname,GLuint * params){
	glGetSamplerParameterIuiv = reinterpret_cast<glGetSamplerParameterIuivCallback>(OpenGLGetProcAddress("glGetSamplerParameterIuiv"));
	glGetSamplerParameterIuiv(sampler,pname,params);
}
glGetSamplerParameterIuivCallback glGetSamplerParameterIuiv = glGetSamplerParameterIuivDispatcher;

void glGetSamplerParameterfvDispatcher(GLuint sampler,GLenum pname,GLfloat * params){
	glGetSamplerParameterfv = reinterpret_cast<glGetSamplerParameterfvCallback>(OpenGLGetProcAddress("glGetSamplerParameterfv"));
	glGetSamplerParameterfv(sampler,pname,params);
}
glGetSamplerParameterfvCallback glGetSamplerParameterfv = glGetSamplerParameterfvDispatcher;

void glGetSamplerParameterivDispatcher(GLuint sampler,GLenum pname,GLint * params){
	glGetSamplerParameteriv = reinterpret_cast<glGetSamplerParameterivCallback>(OpenGLGetProcAddress("glGetSamplerParameteriv"));
	glGetSamplerParameteriv(sampler,pname,params);
}
glGetSamplerParameterivCallback glGetSamplerParameteriv = glGetSamplerParameterivDispatcher;

void glGetShaderInfoLogDispatcher(GLuint shader,GLsizei bufSize,GLsizei * length,GLchar * infoLog){
	glGetShaderInfoLog = reinterpret_cast<glGetShaderInfoLogCallback>(OpenGLGetProcAddress("glGetShaderInfoLog"));
	glGetShaderInfoLog(shader,bufSize,length,infoLog);
}
glGetShaderInfoLogCallback glGetShaderInfoLog = glGetShaderInfoLogDispatcher;

void glGetShaderPrecisionFormatDispatcher(GLenum shadertype,GLenum precisiontype,GLint * range,GLint * precision){
	glGetShaderPrecisionFormat = reinterpret_cast<glGetShaderPrecisionFormatCallback>(OpenGLGetProcAddress("glGetShaderPrecisionFormat"));
	glGetShaderPrecisionFormat(shadertype,precisiontype,range,precision);
}
glGetShaderPrecisionFormatCallback glGetShaderPrecisionFormat = glGetShaderPrecisionFormatDispatcher;

void glGetShaderSourceDispatcher(GLuint shader,GLsizei bufSize,GLsizei * length,GLchar * source){
	glGetShaderSource = reinterpret_cast<glGetShaderSourceCallback>(OpenGLGetProcAddress("glGetShaderSource"));
	glGetShaderSource(shader,bufSize,length,source);
}
glGetShaderSourceCallback glGetShaderSource = glGetShaderSourceDispatcher;

void glGetShaderivDispatcher(GLuint shader,GLenum pname,GLint * params){
	glGetShaderiv = reinterpret_cast<glGetShaderivCallback>(OpenGLGetProcAddress("glGetShaderiv"));
	glGetShaderiv(shader,pname,params);
}
glGetShaderivCallback glGetShaderiv = glGetShaderivDispatcher;

const GLubyte* glGetStringDispatcher(GLenum name){
	glGetString = reinterpret_cast<glGetStringCallback>(OpenGLGetProcAddress("glGetString"));
	return 	glGetString(name);
}
glGetStringCallback glGetString = glGetStringDispatcher;

const GLubyte* glGetStringiDispatcher(GLenum name,GLuint index){
	glGetStringi = reinterpret_cast<glGetStringiCallback>(OpenGLGetProcAddress("glGetStringi"));
	return 	glGetStringi(name,index);
}
glGetStringiCallback glGetStringi = glGetStringiDispatcher;

GLuint glGetSubroutineIndexDispatcher(GLuint program,GLenum shadertype,const GLchar * name){
	glGetSubroutineIndex = reinterpret_cast<glGetSubroutineIndexCallback>(OpenGLGetProcAddress("glGetSubroutineIndex"));
	return 	glGetSubroutineIndex(program,shadertype,name);
}
glGetSubroutineIndexCallback glGetSubroutineIndex = glGetSubroutineIndexDispatcher;

GLint glGetSubroutineUniformLocationDispatcher(GLuint program,GLenum shadertype,const GLchar * name){
	glGetSubroutineUniformLocation = reinterpret_cast<glGetSubroutineUniformLocationCallback>(OpenGLGetProcAddress("glGetSubroutineUniformLocation"));
	return 	glGetSubroutineUniformLocation(program,shadertype,name);
}
glGetSubroutineUniformLocationCallback glGetSubroutineUniformLocation = glGetSubroutineUniformLocationDispatcher;

void glGetSyncivDispatcher(GLsync sync,GLenum pname,GLsizei bufSize,GLsizei * length,GLint * values){
	glGetSynciv = reinterpret_cast<glGetSyncivCallback>(OpenGLGetProcAddress("glGetSynciv"));
	glGetSynciv(sync,pname,bufSize,length,values);
}
glGetSyncivCallback glGetSynciv = glGetSyncivDispatcher;

void glGetTexEnvfvDispatcher(GLenum target,GLenum pname,GLfloat * params){
	glGetTexEnvfv = reinterpret_cast<glGetTexEnvfvCallback>(OpenGLGetProcAddress("glGetTexEnvfv"));
	glGetTexEnvfv(target,pname,params);
}
glGetTexEnvfvCallback glGetTexEnvfv = glGetTexEnvfvDispatcher;

void glGetTexEnvivDispatcher(GLenum target,GLenum pname,GLint * params){
	glGetTexEnviv = reinterpret_cast<glGetTexEnvivCallback>(OpenGLGetProcAddress("glGetTexEnviv"));
	glGetTexEnviv(target,pname,params);
}
glGetTexEnvivCallback glGetTexEnviv = glGetTexEnvivDispatcher;

void glGetTexGendvDispatcher(GLenum coord,GLenum pname,GLdouble * params){
	glGetTexGendv = reinterpret_cast<glGetTexGendvCallback>(OpenGLGetProcAddress("glGetTexGendv"));
	glGetTexGendv(coord,pname,params);
}
glGetTexGendvCallback glGetTexGendv = glGetTexGendvDispatcher;

void glGetTexGenfvDispatcher(GLenum coord,GLenum pname,GLfloat * params){
	glGetTexGenfv = reinterpret_cast<glGetTexGenfvCallback>(OpenGLGetProcAddress("glGetTexGenfv"));
	glGetTexGenfv(coord,pname,params);
}
glGetTexGenfvCallback glGetTexGenfv = glGetTexGenfvDispatcher;

void glGetTexGenivDispatcher(GLenum coord,GLenum pname,GLint * params){
	glGetTexGeniv = reinterpret_cast<glGetTexGenivCallback>(OpenGLGetProcAddress("glGetTexGeniv"));
	glGetTexGeniv(coord,pname,params);
}
glGetTexGenivCallback glGetTexGeniv = glGetTexGenivDispatcher;

void glGetTexImageDispatcher(GLenum target,GLint level,GLenum format,GLenum type,void * pixels){
	glGetTexImage = reinterpret_cast<glGetTexImageCallback>(OpenGLGetProcAddress("glGetTexImage"));
	glGetTexImage(target,level,format,type,pixels);
}
glGetTexImageCallback glGetTexImage = glGetTexImageDispatcher;

void glGetTexLevelParameterfvDispatcher(GLenum target,GLint level,GLenum pname,GLfloat * params){
	glGetTexLevelParameterfv = reinterpret_cast<glGetTexLevelParameterfvCallback>(OpenGLGetProcAddress("glGetTexLevelParameterfv"));
	glGetTexLevelParameterfv(target,level,pname,params);
}
glGetTexLevelParameterfvCallback glGetTexLevelParameterfv = glGetTexLevelParameterfvDispatcher;

void glGetTexLevelParameterivDispatcher(GLenum target,GLint level,GLenum pname,GLint * params){
	glGetTexLevelParameteriv = reinterpret_cast<glGetTexLevelParameterivCallback>(OpenGLGetProcAddress("glGetTexLevelParameteriv"));
	glGetTexLevelParameteriv(target,level,pname,params);
}
glGetTexLevelParameterivCallback glGetTexLevelParameteriv = glGetTexLevelParameterivDispatcher;

void glGetTexParameterIivDispatcher(GLenum target,GLenum pname,GLint * params){
	glGetTexParameterIiv = reinterpret_cast<glGetTexParameterIivCallback>(OpenGLGetProcAddress("glGetTexParameterIiv"));
	glGetTexParameterIiv(target,pname,params);
}
glGetTexParameterIivCallback glGetTexParameterIiv = glGetTexParameterIivDispatcher;

void glGetTexParameterIuivDispatcher(GLenum target,GLenum pname,GLuint * params){
	glGetTexParameterIuiv = reinterpret_cast<glGetTexParameterIuivCallback>(OpenGLGetProcAddress("glGetTexParameterIuiv"));
	glGetTexParameterIuiv(target,pname,params);
}
glGetTexParameterIuivCallback glGetTexParameterIuiv = glGetTexParameterIuivDispatcher;

void glGetTexParameterfvDispatcher(GLenum target,GLenum pname,GLfloat * params){
	glGetTexParameterfv = reinterpret_cast<glGetTexParameterfvCallback>(OpenGLGetProcAddress("glGetTexParameterfv"));
	glGetTexParameterfv(target,pname,params);
}
glGetTexParameterfvCallback glGetTexParameterfv = glGetTexParameterfvDispatcher;

void glGetTexParameterivDispatcher(GLenum target,GLenum pname,GLint * params){
	glGetTexParameteriv = reinterpret_cast<glGetTexParameterivCallback>(OpenGLGetProcAddress("glGetTexParameteriv"));
	glGetTexParameteriv(target,pname,params);
}
glGetTexParameterivCallback glGetTexParameteriv = glGetTexParameterivDispatcher;

void glGetTextureImageDispatcher(GLuint texture,GLint level,GLenum format,GLenum type,GLsizei bufSize,void * pixels){
	glGetTextureImage = reinterpret_cast<glGetTextureImageCallback>(OpenGLGetProcAddress("glGetTextureImage"));
	glGetTextureImage(texture,level,format,type,bufSize,pixels);
}
glGetTextureImageCallback glGetTextureImage = glGetTextureImageDispatcher;

void glGetTextureLevelParameterfvDispatcher(GLuint texture,GLint level,GLenum pname,GLfloat * params){
	glGetTextureLevelParameterfv = reinterpret_cast<glGetTextureLevelParameterfvCallback>(OpenGLGetProcAddress("glGetTextureLevelParameterfv"));
	glGetTextureLevelParameterfv(texture,level,pname,params);
}
glGetTextureLevelParameterfvCallback glGetTextureLevelParameterfv = glGetTextureLevelParameterfvDispatcher;

void glGetTextureLevelParameterivDispatcher(GLuint texture,GLint level,GLenum pname,GLint * params){
	glGetTextureLevelParameteriv = reinterpret_cast<glGetTextureLevelParameterivCallback>(OpenGLGetProcAddress("glGetTextureLevelParameteriv"));
	glGetTextureLevelParameteriv(texture,level,pname,params);
}
glGetTextureLevelParameterivCallback glGetTextureLevelParameteriv = glGetTextureLevelParameterivDispatcher;

void glGetTextureParameterIivDispatcher(GLuint texture,GLenum pname,GLint * params){
	glGetTextureParameterIiv = reinterpret_cast<glGetTextureParameterIivCallback>(OpenGLGetProcAddress("glGetTextureParameterIiv"));
	glGetTextureParameterIiv(texture,pname,params);
}
glGetTextureParameterIivCallback glGetTextureParameterIiv = glGetTextureParameterIivDispatcher;

void glGetTextureParameterIuivDispatcher(GLuint texture,GLenum pname,GLuint * params){
	glGetTextureParameterIuiv = reinterpret_cast<glGetTextureParameterIuivCallback>(OpenGLGetProcAddress("glGetTextureParameterIuiv"));
	glGetTextureParameterIuiv(texture,pname,params);
}
glGetTextureParameterIuivCallback glGetTextureParameterIuiv = glGetTextureParameterIuivDispatcher;

void glGetTextureParameterfvDispatcher(GLuint texture,GLenum pname,GLfloat * params){
	glGetTextureParameterfv = reinterpret_cast<glGetTextureParameterfvCallback>(OpenGLGetProcAddress("glGetTextureParameterfv"));
	glGetTextureParameterfv(texture,pname,params);
}
glGetTextureParameterfvCallback glGetTextureParameterfv = glGetTextureParameterfvDispatcher;

void glGetTextureParameterivDispatcher(GLuint texture,GLenum pname,GLint * params){
	glGetTextureParameteriv = reinterpret_cast<glGetTextureParameterivCallback>(OpenGLGetProcAddress("glGetTextureParameteriv"));
	glGetTextureParameteriv(texture,pname,params);
}
glGetTextureParameterivCallback glGetTextureParameteriv = glGetTextureParameterivDispatcher;

void glGetTextureSubImageDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,GLsizei bufSize,void * pixels){
	glGetTextureSubImage = reinterpret_cast<glGetTextureSubImageCallback>(OpenGLGetProcAddress("glGetTextureSubImage"));
	glGetTextureSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,bufSize,pixels);
}
glGetTextureSubImageCallback glGetTextureSubImage = glGetTextureSubImageDispatcher;

void glGetTransformFeedbackVaryingDispatcher(GLuint program,GLuint index,GLsizei bufSize,GLsizei * length,GLsizei * size,GLenum * type,GLchar * name){
	glGetTransformFeedbackVarying = reinterpret_cast<glGetTransformFeedbackVaryingCallback>(OpenGLGetProcAddress("glGetTransformFeedbackVarying"));
	glGetTransformFeedbackVarying(program,index,bufSize,length,size,type,name);
}
glGetTransformFeedbackVaryingCallback glGetTransformFeedbackVarying = glGetTransformFeedbackVaryingDispatcher;

void glGetTransformFeedbacki64_vDispatcher(GLuint xfb,GLenum pname,GLuint index,GLint64 * param){
	glGetTransformFeedbacki64_v = reinterpret_cast<glGetTransformFeedbacki64_vCallback>(OpenGLGetProcAddress("glGetTransformFeedbacki64_v"));
	glGetTransformFeedbacki64_v(xfb,pname,index,param);
}
glGetTransformFeedbacki64_vCallback glGetTransformFeedbacki64_v = glGetTransformFeedbacki64_vDispatcher;

void glGetTransformFeedbacki_vDispatcher(GLuint xfb,GLenum pname,GLuint index,GLint * param){
	glGetTransformFeedbacki_v = reinterpret_cast<glGetTransformFeedbacki_vCallback>(OpenGLGetProcAddress("glGetTransformFeedbacki_v"));
	glGetTransformFeedbacki_v(xfb,pname,index,param);
}
glGetTransformFeedbacki_vCallback glGetTransformFeedbacki_v = glGetTransformFeedbacki_vDispatcher;

void glGetTransformFeedbackivDispatcher(GLuint xfb,GLenum pname,GLint * param){
	glGetTransformFeedbackiv = reinterpret_cast<glGetTransformFeedbackivCallback>(OpenGLGetProcAddress("glGetTransformFeedbackiv"));
	glGetTransformFeedbackiv(xfb,pname,param);
}
glGetTransformFeedbackivCallback glGetTransformFeedbackiv = glGetTransformFeedbackivDispatcher;

GLuint glGetUniformBlockIndexDispatcher(GLuint program,const GLchar * uniformBlockName){
	glGetUniformBlockIndex = reinterpret_cast<glGetUniformBlockIndexCallback>(OpenGLGetProcAddress("glGetUniformBlockIndex"));
	return 	glGetUniformBlockIndex(program,uniformBlockName);
}
glGetUniformBlockIndexCallback glGetUniformBlockIndex = glGetUniformBlockIndexDispatcher;

void glGetUniformIndicesDispatcher(GLuint program,GLsizei uniformCount,const GLchar *const* uniformNames,GLuint * uniformIndices){
	glGetUniformIndices = reinterpret_cast<glGetUniformIndicesCallback>(OpenGLGetProcAddress("glGetUniformIndices"));
	glGetUniformIndices(program,uniformCount,uniformNames,uniformIndices);
}
glGetUniformIndicesCallback glGetUniformIndices = glGetUniformIndicesDispatcher;

GLint glGetUniformLocationDispatcher(GLuint program,const GLchar * name){
	glGetUniformLocation = reinterpret_cast<glGetUniformLocationCallback>(OpenGLGetProcAddress("glGetUniformLocation"));
	return 	glGetUniformLocation(program,name);
}
glGetUniformLocationCallback glGetUniformLocation = glGetUniformLocationDispatcher;

void glGetUniformSubroutineuivDispatcher(GLenum shadertype,GLint location,GLuint * params){
	glGetUniformSubroutineuiv = reinterpret_cast<glGetUniformSubroutineuivCallback>(OpenGLGetProcAddress("glGetUniformSubroutineuiv"));
	glGetUniformSubroutineuiv(shadertype,location,params);
}
glGetUniformSubroutineuivCallback glGetUniformSubroutineuiv = glGetUniformSubroutineuivDispatcher;

void glGetUniformdvDispatcher(GLuint program,GLint location,GLdouble * params){
	glGetUniformdv = reinterpret_cast<glGetUniformdvCallback>(OpenGLGetProcAddress("glGetUniformdv"));
	glGetUniformdv(program,location,params);
}
glGetUniformdvCallback glGetUniformdv = glGetUniformdvDispatcher;

void glGetUniformfvDispatcher(GLuint program,GLint location,GLfloat * params){
	glGetUniformfv = reinterpret_cast<glGetUniformfvCallback>(OpenGLGetProcAddress("glGetUniformfv"));
	glGetUniformfv(program,location,params);
}
glGetUniformfvCallback glGetUniformfv = glGetUniformfvDispatcher;

void glGetUniformivDispatcher(GLuint program,GLint location,GLint * params){
	glGetUniformiv = reinterpret_cast<glGetUniformivCallback>(OpenGLGetProcAddress("glGetUniformiv"));
	glGetUniformiv(program,location,params);
}
glGetUniformivCallback glGetUniformiv = glGetUniformivDispatcher;

void glGetUniformuivDispatcher(GLuint program,GLint location,GLuint * params){
	glGetUniformuiv = reinterpret_cast<glGetUniformuivCallback>(OpenGLGetProcAddress("glGetUniformuiv"));
	glGetUniformuiv(program,location,params);
}
glGetUniformuivCallback glGetUniformuiv = glGetUniformuivDispatcher;

void glGetVertexArrayIndexed64ivDispatcher(GLuint vaobj,GLuint index,GLenum pname,GLint64 * param){
	glGetVertexArrayIndexed64iv = reinterpret_cast<glGetVertexArrayIndexed64ivCallback>(OpenGLGetProcAddress("glGetVertexArrayIndexed64iv"));
	glGetVertexArrayIndexed64iv(vaobj,index,pname,param);
}
glGetVertexArrayIndexed64ivCallback glGetVertexArrayIndexed64iv = glGetVertexArrayIndexed64ivDispatcher;

void glGetVertexArrayIndexedivDispatcher(GLuint vaobj,GLuint index,GLenum pname,GLint * param){
	glGetVertexArrayIndexediv = reinterpret_cast<glGetVertexArrayIndexedivCallback>(OpenGLGetProcAddress("glGetVertexArrayIndexediv"));
	glGetVertexArrayIndexediv(vaobj,index,pname,param);
}
glGetVertexArrayIndexedivCallback glGetVertexArrayIndexediv = glGetVertexArrayIndexedivDispatcher;

void glGetVertexArrayivDispatcher(GLuint vaobj,GLenum pname,GLint * param){
	glGetVertexArrayiv = reinterpret_cast<glGetVertexArrayivCallback>(OpenGLGetProcAddress("glGetVertexArrayiv"));
	glGetVertexArrayiv(vaobj,pname,param);
}
glGetVertexArrayivCallback glGetVertexArrayiv = glGetVertexArrayivDispatcher;

void glGetVertexAttribIivDispatcher(GLuint index,GLenum pname,GLint * params){
	glGetVertexAttribIiv = reinterpret_cast<glGetVertexAttribIivCallback>(OpenGLGetProcAddress("glGetVertexAttribIiv"));
	glGetVertexAttribIiv(index,pname,params);
}
glGetVertexAttribIivCallback glGetVertexAttribIiv = glGetVertexAttribIivDispatcher;

void glGetVertexAttribIuivDispatcher(GLuint index,GLenum pname,GLuint * params){
	glGetVertexAttribIuiv = reinterpret_cast<glGetVertexAttribIuivCallback>(OpenGLGetProcAddress("glGetVertexAttribIuiv"));
	glGetVertexAttribIuiv(index,pname,params);
}
glGetVertexAttribIuivCallback glGetVertexAttribIuiv = glGetVertexAttribIuivDispatcher;

void glGetVertexAttribLdvDispatcher(GLuint index,GLenum pname,GLdouble * params){
	glGetVertexAttribLdv = reinterpret_cast<glGetVertexAttribLdvCallback>(OpenGLGetProcAddress("glGetVertexAttribLdv"));
	glGetVertexAttribLdv(index,pname,params);
}
glGetVertexAttribLdvCallback glGetVertexAttribLdv = glGetVertexAttribLdvDispatcher;

void glGetVertexAttribPointervDispatcher(GLuint index,GLenum pname,void ** pointer){
	glGetVertexAttribPointerv = reinterpret_cast<glGetVertexAttribPointervCallback>(OpenGLGetProcAddress("glGetVertexAttribPointerv"));
	glGetVertexAttribPointerv(index,pname,pointer);
}
glGetVertexAttribPointervCallback glGetVertexAttribPointerv = glGetVertexAttribPointervDispatcher;

void glGetVertexAttribdvDispatcher(GLuint index,GLenum pname,GLdouble * params){
	glGetVertexAttribdv = reinterpret_cast<glGetVertexAttribdvCallback>(OpenGLGetProcAddress("glGetVertexAttribdv"));
	glGetVertexAttribdv(index,pname,params);
}
glGetVertexAttribdvCallback glGetVertexAttribdv = glGetVertexAttribdvDispatcher;

void glGetVertexAttribfvDispatcher(GLuint index,GLenum pname,GLfloat * params){
	glGetVertexAttribfv = reinterpret_cast<glGetVertexAttribfvCallback>(OpenGLGetProcAddress("glGetVertexAttribfv"));
	glGetVertexAttribfv(index,pname,params);
}
glGetVertexAttribfvCallback glGetVertexAttribfv = glGetVertexAttribfvDispatcher;

void glGetVertexAttribivDispatcher(GLuint index,GLenum pname,GLint * params){
	glGetVertexAttribiv = reinterpret_cast<glGetVertexAttribivCallback>(OpenGLGetProcAddress("glGetVertexAttribiv"));
	glGetVertexAttribiv(index,pname,params);
}
glGetVertexAttribivCallback glGetVertexAttribiv = glGetVertexAttribivDispatcher;

void glGetnColorTableDispatcher(GLenum target,GLenum format,GLenum type,GLsizei bufSize,void * table){
	glGetnColorTable = reinterpret_cast<glGetnColorTableCallback>(OpenGLGetProcAddress("glGetnColorTable"));
	glGetnColorTable(target,format,type,bufSize,table);
}
glGetnColorTableCallback glGetnColorTable = glGetnColorTableDispatcher;

void glGetnCompressedTexImageDispatcher(GLenum target,GLint lod,GLsizei bufSize,void * pixels){
	glGetnCompressedTexImage = reinterpret_cast<glGetnCompressedTexImageCallback>(OpenGLGetProcAddress("glGetnCompressedTexImage"));
	glGetnCompressedTexImage(target,lod,bufSize,pixels);
}
glGetnCompressedTexImageCallback glGetnCompressedTexImage = glGetnCompressedTexImageDispatcher;

void glGetnConvolutionFilterDispatcher(GLenum target,GLenum format,GLenum type,GLsizei bufSize,void * image){
	glGetnConvolutionFilter = reinterpret_cast<glGetnConvolutionFilterCallback>(OpenGLGetProcAddress("glGetnConvolutionFilter"));
	glGetnConvolutionFilter(target,format,type,bufSize,image);
}
glGetnConvolutionFilterCallback glGetnConvolutionFilter = glGetnConvolutionFilterDispatcher;

void glGetnHistogramDispatcher(GLenum target,GLboolean reset,GLenum format,GLenum type,GLsizei bufSize,void * values){
	glGetnHistogram = reinterpret_cast<glGetnHistogramCallback>(OpenGLGetProcAddress("glGetnHistogram"));
	glGetnHistogram(target,reset,format,type,bufSize,values);
}
glGetnHistogramCallback glGetnHistogram = glGetnHistogramDispatcher;

void glGetnMapdvDispatcher(GLenum target,GLenum query,GLsizei bufSize,GLdouble * v){
	glGetnMapdv = reinterpret_cast<glGetnMapdvCallback>(OpenGLGetProcAddress("glGetnMapdv"));
	glGetnMapdv(target,query,bufSize,v);
}
glGetnMapdvCallback glGetnMapdv = glGetnMapdvDispatcher;

void glGetnMapfvDispatcher(GLenum target,GLenum query,GLsizei bufSize,GLfloat * v){
	glGetnMapfv = reinterpret_cast<glGetnMapfvCallback>(OpenGLGetProcAddress("glGetnMapfv"));
	glGetnMapfv(target,query,bufSize,v);
}
glGetnMapfvCallback glGetnMapfv = glGetnMapfvDispatcher;

void glGetnMapivDispatcher(GLenum target,GLenum query,GLsizei bufSize,GLint * v){
	glGetnMapiv = reinterpret_cast<glGetnMapivCallback>(OpenGLGetProcAddress("glGetnMapiv"));
	glGetnMapiv(target,query,bufSize,v);
}
glGetnMapivCallback glGetnMapiv = glGetnMapivDispatcher;

void glGetnMinmaxDispatcher(GLenum target,GLboolean reset,GLenum format,GLenum type,GLsizei bufSize,void * values){
	glGetnMinmax = reinterpret_cast<glGetnMinmaxCallback>(OpenGLGetProcAddress("glGetnMinmax"));
	glGetnMinmax(target,reset,format,type,bufSize,values);
}
glGetnMinmaxCallback glGetnMinmax = glGetnMinmaxDispatcher;

void glGetnPixelMapfvDispatcher(GLenum map,GLsizei bufSize,GLfloat * values){
	glGetnPixelMapfv = reinterpret_cast<glGetnPixelMapfvCallback>(OpenGLGetProcAddress("glGetnPixelMapfv"));
	glGetnPixelMapfv(map,bufSize,values);
}
glGetnPixelMapfvCallback glGetnPixelMapfv = glGetnPixelMapfvDispatcher;

void glGetnPixelMapuivDispatcher(GLenum map,GLsizei bufSize,GLuint * values){
	glGetnPixelMapuiv = reinterpret_cast<glGetnPixelMapuivCallback>(OpenGLGetProcAddress("glGetnPixelMapuiv"));
	glGetnPixelMapuiv(map,bufSize,values);
}
glGetnPixelMapuivCallback glGetnPixelMapuiv = glGetnPixelMapuivDispatcher;

void glGetnPixelMapusvDispatcher(GLenum map,GLsizei bufSize,GLushort * values){
	glGetnPixelMapusv = reinterpret_cast<glGetnPixelMapusvCallback>(OpenGLGetProcAddress("glGetnPixelMapusv"));
	glGetnPixelMapusv(map,bufSize,values);
}
glGetnPixelMapusvCallback glGetnPixelMapusv = glGetnPixelMapusvDispatcher;

void glGetnPolygonStippleDispatcher(GLsizei bufSize,GLubyte * pattern){
	glGetnPolygonStipple = reinterpret_cast<glGetnPolygonStippleCallback>(OpenGLGetProcAddress("glGetnPolygonStipple"));
	glGetnPolygonStipple(bufSize,pattern);
}
glGetnPolygonStippleCallback glGetnPolygonStipple = glGetnPolygonStippleDispatcher;

void glGetnSeparableFilterDispatcher(GLenum target,GLenum format,GLenum type,GLsizei rowBufSize,void * row,GLsizei columnBufSize,void * column,void * span){
	glGetnSeparableFilter = reinterpret_cast<glGetnSeparableFilterCallback>(OpenGLGetProcAddress("glGetnSeparableFilter"));
	glGetnSeparableFilter(target,format,type,rowBufSize,row,columnBufSize,column,span);
}
glGetnSeparableFilterCallback glGetnSeparableFilter = glGetnSeparableFilterDispatcher;

void glGetnTexImageDispatcher(GLenum target,GLint level,GLenum format,GLenum type,GLsizei bufSize,void * pixels){
	glGetnTexImage = reinterpret_cast<glGetnTexImageCallback>(OpenGLGetProcAddress("glGetnTexImage"));
	glGetnTexImage(target,level,format,type,bufSize,pixels);
}
glGetnTexImageCallback glGetnTexImage = glGetnTexImageDispatcher;

void glGetnUniformdvDispatcher(GLuint program,GLint location,GLsizei bufSize,GLdouble * params){
	glGetnUniformdv = reinterpret_cast<glGetnUniformdvCallback>(OpenGLGetProcAddress("glGetnUniformdv"));
	glGetnUniformdv(program,location,bufSize,params);
}
glGetnUniformdvCallback glGetnUniformdv = glGetnUniformdvDispatcher;

void glGetnUniformfvDispatcher(GLuint program,GLint location,GLsizei bufSize,GLfloat * params){
	glGetnUniformfv = reinterpret_cast<glGetnUniformfvCallback>(OpenGLGetProcAddress("glGetnUniformfv"));
	glGetnUniformfv(program,location,bufSize,params);
}
glGetnUniformfvCallback glGetnUniformfv = glGetnUniformfvDispatcher;

void glGetnUniformivDispatcher(GLuint program,GLint location,GLsizei bufSize,GLint * params){
	glGetnUniformiv = reinterpret_cast<glGetnUniformivCallback>(OpenGLGetProcAddress("glGetnUniformiv"));
	glGetnUniformiv(program,location,bufSize,params);
}
glGetnUniformivCallback glGetnUniformiv = glGetnUniformivDispatcher;

void glGetnUniformuivDispatcher(GLuint program,GLint location,GLsizei bufSize,GLuint * params){
	glGetnUniformuiv = reinterpret_cast<glGetnUniformuivCallback>(OpenGLGetProcAddress("glGetnUniformuiv"));
	glGetnUniformuiv(program,location,bufSize,params);
}
glGetnUniformuivCallback glGetnUniformuiv = glGetnUniformuivDispatcher;

void glHintDispatcher(GLenum target,GLenum mode){
	glHint = reinterpret_cast<glHintCallback>(OpenGLGetProcAddress("glHint"));
	glHint(target,mode);
}
glHintCallback glHint = glHintDispatcher;

void glIndexMaskDispatcher(GLuint mask){
	glIndexMask = reinterpret_cast<glIndexMaskCallback>(OpenGLGetProcAddress("glIndexMask"));
	glIndexMask(mask);
}
glIndexMaskCallback glIndexMask = glIndexMaskDispatcher;

void glIndexPointerDispatcher(GLenum type,GLsizei stride,const void * pointer){
	glIndexPointer = reinterpret_cast<glIndexPointerCallback>(OpenGLGetProcAddress("glIndexPointer"));
	glIndexPointer(type,stride,pointer);
}
glIndexPointerCallback glIndexPointer = glIndexPointerDispatcher;

void glIndexdDispatcher(GLdouble c){
	glIndexd = reinterpret_cast<glIndexdCallback>(OpenGLGetProcAddress("glIndexd"));
	glIndexd(c);
}
glIndexdCallback glIndexd = glIndexdDispatcher;

void glIndexdvDispatcher(const GLdouble * c){
	glIndexdv = reinterpret_cast<glIndexdvCallback>(OpenGLGetProcAddress("glIndexdv"));
	glIndexdv(c);
}
glIndexdvCallback glIndexdv = glIndexdvDispatcher;

void glIndexfDispatcher(GLfloat c){
	glIndexf = reinterpret_cast<glIndexfCallback>(OpenGLGetProcAddress("glIndexf"));
	glIndexf(c);
}
glIndexfCallback glIndexf = glIndexfDispatcher;

void glIndexfvDispatcher(const GLfloat * c){
	glIndexfv = reinterpret_cast<glIndexfvCallback>(OpenGLGetProcAddress("glIndexfv"));
	glIndexfv(c);
}
glIndexfvCallback glIndexfv = glIndexfvDispatcher;

void glIndexiDispatcher(GLint c){
	glIndexi = reinterpret_cast<glIndexiCallback>(OpenGLGetProcAddress("glIndexi"));
	glIndexi(c);
}
glIndexiCallback glIndexi = glIndexiDispatcher;

void glIndexivDispatcher(const GLint * c){
	glIndexiv = reinterpret_cast<glIndexivCallback>(OpenGLGetProcAddress("glIndexiv"));
	glIndexiv(c);
}
glIndexivCallback glIndexiv = glIndexivDispatcher;

void glIndexsDispatcher(GLshort c){
	glIndexs = reinterpret_cast<glIndexsCallback>(OpenGLGetProcAddress("glIndexs"));
	glIndexs(c);
}
glIndexsCallback glIndexs = glIndexsDispatcher;

void glIndexsvDispatcher(const GLshort * c){
	glIndexsv = reinterpret_cast<glIndexsvCallback>(OpenGLGetProcAddress("glIndexsv"));
	glIndexsv(c);
}
glIndexsvCallback glIndexsv = glIndexsvDispatcher;

void glIndexubDispatcher(GLubyte c){
	glIndexub = reinterpret_cast<glIndexubCallback>(OpenGLGetProcAddress("glIndexub"));
	glIndexub(c);
}
glIndexubCallback glIndexub = glIndexubDispatcher;

void glIndexubvDispatcher(const GLubyte * c){
	glIndexubv = reinterpret_cast<glIndexubvCallback>(OpenGLGetProcAddress("glIndexubv"));
	glIndexubv(c);
}
glIndexubvCallback glIndexubv = glIndexubvDispatcher;

void glInitNamesDispatcher(){
	glInitNames = reinterpret_cast<glInitNamesCallback>(OpenGLGetProcAddress("glInitNames"));
	glInitNames();
}
glInitNamesCallback glInitNames = glInitNamesDispatcher;

void glInterleavedArraysDispatcher(GLenum format,GLsizei stride,const void * pointer){
	glInterleavedArrays = reinterpret_cast<glInterleavedArraysCallback>(OpenGLGetProcAddress("glInterleavedArrays"));
	glInterleavedArrays(format,stride,pointer);
}
glInterleavedArraysCallback glInterleavedArrays = glInterleavedArraysDispatcher;

void glInvalidateBufferDataDispatcher(GLuint buffer){
	glInvalidateBufferData = reinterpret_cast<glInvalidateBufferDataCallback>(OpenGLGetProcAddress("glInvalidateBufferData"));
	glInvalidateBufferData(buffer);
}
glInvalidateBufferDataCallback glInvalidateBufferData = glInvalidateBufferDataDispatcher;

void glInvalidateBufferSubDataDispatcher(GLuint buffer,GLintptr offset,GLsizeiptr length){
	glInvalidateBufferSubData = reinterpret_cast<glInvalidateBufferSubDataCallback>(OpenGLGetProcAddress("glInvalidateBufferSubData"));
	glInvalidateBufferSubData(buffer,offset,length);
}
glInvalidateBufferSubDataCallback glInvalidateBufferSubData = glInvalidateBufferSubDataDispatcher;

void glInvalidateFramebufferDispatcher(GLenum target,GLsizei numAttachments,const GLenum * attachments){
	glInvalidateFramebuffer = reinterpret_cast<glInvalidateFramebufferCallback>(OpenGLGetProcAddress("glInvalidateFramebuffer"));
	glInvalidateFramebuffer(target,numAttachments,attachments);
}
glInvalidateFramebufferCallback glInvalidateFramebuffer = glInvalidateFramebufferDispatcher;

void glInvalidateNamedFramebufferDataDispatcher(GLuint framebuffer,GLsizei numAttachments,const GLenum * attachments){
	glInvalidateNamedFramebufferData = reinterpret_cast<glInvalidateNamedFramebufferDataCallback>(OpenGLGetProcAddress("glInvalidateNamedFramebufferData"));
	glInvalidateNamedFramebufferData(framebuffer,numAttachments,attachments);
}
glInvalidateNamedFramebufferDataCallback glInvalidateNamedFramebufferData = glInvalidateNamedFramebufferDataDispatcher;

void glInvalidateNamedFramebufferSubDataDispatcher(GLuint framebuffer,GLsizei numAttachments,const GLenum * attachments,GLint x,GLint y,GLsizei width,GLsizei height){
	glInvalidateNamedFramebufferSubData = reinterpret_cast<glInvalidateNamedFramebufferSubDataCallback>(OpenGLGetProcAddress("glInvalidateNamedFramebufferSubData"));
	glInvalidateNamedFramebufferSubData(framebuffer,numAttachments,attachments,x,y,width,height);
}
glInvalidateNamedFramebufferSubDataCallback glInvalidateNamedFramebufferSubData = glInvalidateNamedFramebufferSubDataDispatcher;

void glInvalidateSubFramebufferDispatcher(GLenum target,GLsizei numAttachments,const GLenum * attachments,GLint x,GLint y,GLsizei width,GLsizei height){
	glInvalidateSubFramebuffer = reinterpret_cast<glInvalidateSubFramebufferCallback>(OpenGLGetProcAddress("glInvalidateSubFramebuffer"));
	glInvalidateSubFramebuffer(target,numAttachments,attachments,x,y,width,height);
}
glInvalidateSubFramebufferCallback glInvalidateSubFramebuffer = glInvalidateSubFramebufferDispatcher;

void glInvalidateTexImageDispatcher(GLuint texture,GLint level){
	glInvalidateTexImage = reinterpret_cast<glInvalidateTexImageCallback>(OpenGLGetProcAddress("glInvalidateTexImage"));
	glInvalidateTexImage(texture,level);
}
glInvalidateTexImageCallback glInvalidateTexImage = glInvalidateTexImageDispatcher;

void glInvalidateTexSubImageDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth){
	glInvalidateTexSubImage = reinterpret_cast<glInvalidateTexSubImageCallback>(OpenGLGetProcAddress("glInvalidateTexSubImage"));
	glInvalidateTexSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth);
}
glInvalidateTexSubImageCallback glInvalidateTexSubImage = glInvalidateTexSubImageDispatcher;

GLboolean glIsBufferDispatcher(GLuint buffer){
	glIsBuffer = reinterpret_cast<glIsBufferCallback>(OpenGLGetProcAddress("glIsBuffer"));
	return 	glIsBuffer(buffer);
}
glIsBufferCallback glIsBuffer = glIsBufferDispatcher;

GLboolean glIsEnabledDispatcher(GLenum cap){
	glIsEnabled = reinterpret_cast<glIsEnabledCallback>(OpenGLGetProcAddress("glIsEnabled"));
	return 	glIsEnabled(cap);
}
glIsEnabledCallback glIsEnabled = glIsEnabledDispatcher;

GLboolean glIsEnablediDispatcher(GLenum target,GLuint index){
	glIsEnabledi = reinterpret_cast<glIsEnablediCallback>(OpenGLGetProcAddress("glIsEnabledi"));
	return 	glIsEnabledi(target,index);
}
glIsEnablediCallback glIsEnabledi = glIsEnablediDispatcher;

GLboolean glIsFramebufferDispatcher(GLuint framebuffer){
	glIsFramebuffer = reinterpret_cast<glIsFramebufferCallback>(OpenGLGetProcAddress("glIsFramebuffer"));
	return 	glIsFramebuffer(framebuffer);
}
glIsFramebufferCallback glIsFramebuffer = glIsFramebufferDispatcher;

GLboolean glIsListDispatcher(GLuint list){
	glIsList = reinterpret_cast<glIsListCallback>(OpenGLGetProcAddress("glIsList"));
	return 	glIsList(list);
}
glIsListCallback glIsList = glIsListDispatcher;

GLboolean glIsProgramDispatcher(GLuint program){
	glIsProgram = reinterpret_cast<glIsProgramCallback>(OpenGLGetProcAddress("glIsProgram"));
	return 	glIsProgram(program);
}
glIsProgramCallback glIsProgram = glIsProgramDispatcher;

GLboolean glIsProgramPipelineDispatcher(GLuint pipeline){
	glIsProgramPipeline = reinterpret_cast<glIsProgramPipelineCallback>(OpenGLGetProcAddress("glIsProgramPipeline"));
	return 	glIsProgramPipeline(pipeline);
}
glIsProgramPipelineCallback glIsProgramPipeline = glIsProgramPipelineDispatcher;

GLboolean glIsQueryDispatcher(GLuint id){
	glIsQuery = reinterpret_cast<glIsQueryCallback>(OpenGLGetProcAddress("glIsQuery"));
	return 	glIsQuery(id);
}
glIsQueryCallback glIsQuery = glIsQueryDispatcher;

GLboolean glIsRenderbufferDispatcher(GLuint renderbuffer){
	glIsRenderbuffer = reinterpret_cast<glIsRenderbufferCallback>(OpenGLGetProcAddress("glIsRenderbuffer"));
	return 	glIsRenderbuffer(renderbuffer);
}
glIsRenderbufferCallback glIsRenderbuffer = glIsRenderbufferDispatcher;

GLboolean glIsSamplerDispatcher(GLuint sampler){
	glIsSampler = reinterpret_cast<glIsSamplerCallback>(OpenGLGetProcAddress("glIsSampler"));
	return 	glIsSampler(sampler);
}
glIsSamplerCallback glIsSampler = glIsSamplerDispatcher;

GLboolean glIsShaderDispatcher(GLuint shader){
	glIsShader = reinterpret_cast<glIsShaderCallback>(OpenGLGetProcAddress("glIsShader"));
	return 	glIsShader(shader);
}
glIsShaderCallback glIsShader = glIsShaderDispatcher;

GLboolean glIsSyncDispatcher(GLsync sync){
	glIsSync = reinterpret_cast<glIsSyncCallback>(OpenGLGetProcAddress("glIsSync"));
	return 	glIsSync(sync);
}
glIsSyncCallback glIsSync = glIsSyncDispatcher;

GLboolean glIsTextureDispatcher(GLuint texture){
	glIsTexture = reinterpret_cast<glIsTextureCallback>(OpenGLGetProcAddress("glIsTexture"));
	return 	glIsTexture(texture);
}
glIsTextureCallback glIsTexture = glIsTextureDispatcher;

GLboolean glIsTransformFeedbackDispatcher(GLuint id){
	glIsTransformFeedback = reinterpret_cast<glIsTransformFeedbackCallback>(OpenGLGetProcAddress("glIsTransformFeedback"));
	return 	glIsTransformFeedback(id);
}
glIsTransformFeedbackCallback glIsTransformFeedback = glIsTransformFeedbackDispatcher;

GLboolean glIsVertexArrayDispatcher(GLuint array){
	glIsVertexArray = reinterpret_cast<glIsVertexArrayCallback>(OpenGLGetProcAddress("glIsVertexArray"));
	return 	glIsVertexArray(array);
}
glIsVertexArrayCallback glIsVertexArray = glIsVertexArrayDispatcher;

void glLightModelfDispatcher(GLenum pname,GLfloat param){
	glLightModelf = reinterpret_cast<glLightModelfCallback>(OpenGLGetProcAddress("glLightModelf"));
	glLightModelf(pname,param);
}
glLightModelfCallback glLightModelf = glLightModelfDispatcher;

void glLightModelfvDispatcher(GLenum pname,const GLfloat * params){
	glLightModelfv = reinterpret_cast<glLightModelfvCallback>(OpenGLGetProcAddress("glLightModelfv"));
	glLightModelfv(pname,params);
}
glLightModelfvCallback glLightModelfv = glLightModelfvDispatcher;

void glLightModeliDispatcher(GLenum pname,GLint param){
	glLightModeli = reinterpret_cast<glLightModeliCallback>(OpenGLGetProcAddress("glLightModeli"));
	glLightModeli(pname,param);
}
glLightModeliCallback glLightModeli = glLightModeliDispatcher;

void glLightModelivDispatcher(GLenum pname,const GLint * params){
	glLightModeliv = reinterpret_cast<glLightModelivCallback>(OpenGLGetProcAddress("glLightModeliv"));
	glLightModeliv(pname,params);
}
glLightModelivCallback glLightModeliv = glLightModelivDispatcher;

void glLightfDispatcher(GLenum light,GLenum pname,GLfloat param){
	glLightf = reinterpret_cast<glLightfCallback>(OpenGLGetProcAddress("glLightf"));
	glLightf(light,pname,param);
}
glLightfCallback glLightf = glLightfDispatcher;

void glLightfvDispatcher(GLenum light,GLenum pname,const GLfloat * params){
	glLightfv = reinterpret_cast<glLightfvCallback>(OpenGLGetProcAddress("glLightfv"));
	glLightfv(light,pname,params);
}
glLightfvCallback glLightfv = glLightfvDispatcher;

void glLightiDispatcher(GLenum light,GLenum pname,GLint param){
	glLighti = reinterpret_cast<glLightiCallback>(OpenGLGetProcAddress("glLighti"));
	glLighti(light,pname,param);
}
glLightiCallback glLighti = glLightiDispatcher;

void glLightivDispatcher(GLenum light,GLenum pname,const GLint * params){
	glLightiv = reinterpret_cast<glLightivCallback>(OpenGLGetProcAddress("glLightiv"));
	glLightiv(light,pname,params);
}
glLightivCallback glLightiv = glLightivDispatcher;

void glLineStippleDispatcher(GLint factor,GLushort pattern){
	glLineStipple = reinterpret_cast<glLineStippleCallback>(OpenGLGetProcAddress("glLineStipple"));
	glLineStipple(factor,pattern);
}
glLineStippleCallback glLineStipple = glLineStippleDispatcher;

void glLineWidthDispatcher(GLfloat width){
	glLineWidth = reinterpret_cast<glLineWidthCallback>(OpenGLGetProcAddress("glLineWidth"));
	glLineWidth(width);
}
glLineWidthCallback glLineWidth = glLineWidthDispatcher;

void glLinkProgramDispatcher(GLuint program){
	glLinkProgram = reinterpret_cast<glLinkProgramCallback>(OpenGLGetProcAddress("glLinkProgram"));
	glLinkProgram(program);
}
glLinkProgramCallback glLinkProgram = glLinkProgramDispatcher;

void glListBaseDispatcher(GLuint base){
	glListBase = reinterpret_cast<glListBaseCallback>(OpenGLGetProcAddress("glListBase"));
	glListBase(base);
}
glListBaseCallback glListBase = glListBaseDispatcher;

void glLoadIdentityDispatcher(){
	glLoadIdentity = reinterpret_cast<glLoadIdentityCallback>(OpenGLGetProcAddress("glLoadIdentity"));
	glLoadIdentity();
}
glLoadIdentityCallback glLoadIdentity = glLoadIdentityDispatcher;

void glLoadMatrixdDispatcher(const GLdouble * m){
	glLoadMatrixd = reinterpret_cast<glLoadMatrixdCallback>(OpenGLGetProcAddress("glLoadMatrixd"));
	glLoadMatrixd(m);
}
glLoadMatrixdCallback glLoadMatrixd = glLoadMatrixdDispatcher;

void glLoadMatrixfDispatcher(const GLfloat * m){
	glLoadMatrixf = reinterpret_cast<glLoadMatrixfCallback>(OpenGLGetProcAddress("glLoadMatrixf"));
	glLoadMatrixf(m);
}
glLoadMatrixfCallback glLoadMatrixf = glLoadMatrixfDispatcher;

void glLoadNameDispatcher(GLuint name){
	glLoadName = reinterpret_cast<glLoadNameCallback>(OpenGLGetProcAddress("glLoadName"));
	glLoadName(name);
}
glLoadNameCallback glLoadName = glLoadNameDispatcher;

void glLoadTransposeMatrixdDispatcher(const GLdouble * m){
	glLoadTransposeMatrixd = reinterpret_cast<glLoadTransposeMatrixdCallback>(OpenGLGetProcAddress("glLoadTransposeMatrixd"));
	glLoadTransposeMatrixd(m);
}
glLoadTransposeMatrixdCallback glLoadTransposeMatrixd = glLoadTransposeMatrixdDispatcher;

void glLoadTransposeMatrixfDispatcher(const GLfloat * m){
	glLoadTransposeMatrixf = reinterpret_cast<glLoadTransposeMatrixfCallback>(OpenGLGetProcAddress("glLoadTransposeMatrixf"));
	glLoadTransposeMatrixf(m);
}
glLoadTransposeMatrixfCallback glLoadTransposeMatrixf = glLoadTransposeMatrixfDispatcher;

void glLogicOpDispatcher(GLenum opcode){
	glLogicOp = reinterpret_cast<glLogicOpCallback>(OpenGLGetProcAddress("glLogicOp"));
	glLogicOp(opcode);
}
glLogicOpCallback glLogicOp = glLogicOpDispatcher;

void glMap1dDispatcher(GLenum target,GLdouble u1,GLdouble u2,GLint stride,GLint order,const GLdouble * points){
	glMap1d = reinterpret_cast<glMap1dCallback>(OpenGLGetProcAddress("glMap1d"));
	glMap1d(target,u1,u2,stride,order,points);
}
glMap1dCallback glMap1d = glMap1dDispatcher;

void glMap1fDispatcher(GLenum target,GLfloat u1,GLfloat u2,GLint stride,GLint order,const GLfloat * points){
	glMap1f = reinterpret_cast<glMap1fCallback>(OpenGLGetProcAddress("glMap1f"));
	glMap1f(target,u1,u2,stride,order,points);
}
glMap1fCallback glMap1f = glMap1fDispatcher;

void glMap2dDispatcher(GLenum target,GLdouble u1,GLdouble u2,GLint ustride,GLint uorder,GLdouble v1,GLdouble v2,GLint vstride,GLint vorder,const GLdouble * points){
	glMap2d = reinterpret_cast<glMap2dCallback>(OpenGLGetProcAddress("glMap2d"));
	glMap2d(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);
}
glMap2dCallback glMap2d = glMap2dDispatcher;

void glMap2fDispatcher(GLenum target,GLfloat u1,GLfloat u2,GLint ustride,GLint uorder,GLfloat v1,GLfloat v2,GLint vstride,GLint vorder,const GLfloat * points){
	glMap2f = reinterpret_cast<glMap2fCallback>(OpenGLGetProcAddress("glMap2f"));
	glMap2f(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);
}
glMap2fCallback glMap2f = glMap2fDispatcher;

void glMapBufferDispatcher(GLenum target,GLenum access){
	glMapBuffer = reinterpret_cast<glMapBufferCallback>(OpenGLGetProcAddress("glMapBuffer"));
	glMapBuffer(target,access);
}
glMapBufferCallback glMapBuffer = glMapBufferDispatcher;

void glMapBufferRangeDispatcher(GLenum target,GLintptr offset,GLsizeiptr length,GLbitfield access){
	glMapBufferRange = reinterpret_cast<glMapBufferRangeCallback>(OpenGLGetProcAddress("glMapBufferRange"));
	glMapBufferRange(target,offset,length,access);
}
glMapBufferRangeCallback glMapBufferRange = glMapBufferRangeDispatcher;

void glMapGrid1dDispatcher(GLint un,GLdouble u1,GLdouble u2){
	glMapGrid1d = reinterpret_cast<glMapGrid1dCallback>(OpenGLGetProcAddress("glMapGrid1d"));
	glMapGrid1d(un,u1,u2);
}
glMapGrid1dCallback glMapGrid1d = glMapGrid1dDispatcher;

void glMapGrid1fDispatcher(GLint un,GLfloat u1,GLfloat u2){
	glMapGrid1f = reinterpret_cast<glMapGrid1fCallback>(OpenGLGetProcAddress("glMapGrid1f"));
	glMapGrid1f(un,u1,u2);
}
glMapGrid1fCallback glMapGrid1f = glMapGrid1fDispatcher;

void glMapGrid2dDispatcher(GLint un,GLdouble u1,GLdouble u2,GLint vn,GLdouble v1,GLdouble v2){
	glMapGrid2d = reinterpret_cast<glMapGrid2dCallback>(OpenGLGetProcAddress("glMapGrid2d"));
	glMapGrid2d(un,u1,u2,vn,v1,v2);
}
glMapGrid2dCallback glMapGrid2d = glMapGrid2dDispatcher;

void glMapGrid2fDispatcher(GLint un,GLfloat u1,GLfloat u2,GLint vn,GLfloat v1,GLfloat v2){
	glMapGrid2f = reinterpret_cast<glMapGrid2fCallback>(OpenGLGetProcAddress("glMapGrid2f"));
	glMapGrid2f(un,u1,u2,vn,v1,v2);
}
glMapGrid2fCallback glMapGrid2f = glMapGrid2fDispatcher;

void glMapNamedBufferDispatcher(GLuint buffer,GLenum access){
	glMapNamedBuffer = reinterpret_cast<glMapNamedBufferCallback>(OpenGLGetProcAddress("glMapNamedBuffer"));
	glMapNamedBuffer(buffer,access);
}
glMapNamedBufferCallback glMapNamedBuffer = glMapNamedBufferDispatcher;

void glMapNamedBufferRangeDispatcher(GLuint buffer,GLintptr offset,GLsizei length,GLbitfield access){
	glMapNamedBufferRange = reinterpret_cast<glMapNamedBufferRangeCallback>(OpenGLGetProcAddress("glMapNamedBufferRange"));
	glMapNamedBufferRange(buffer,offset,length,access);
}
glMapNamedBufferRangeCallback glMapNamedBufferRange = glMapNamedBufferRangeDispatcher;

void glMaterialfDispatcher(GLenum face,GLenum pname,GLfloat param){
	glMaterialf = reinterpret_cast<glMaterialfCallback>(OpenGLGetProcAddress("glMaterialf"));
	glMaterialf(face,pname,param);
}
glMaterialfCallback glMaterialf = glMaterialfDispatcher;

void glMaterialfvDispatcher(GLenum face,GLenum pname,const GLfloat * params){
	glMaterialfv = reinterpret_cast<glMaterialfvCallback>(OpenGLGetProcAddress("glMaterialfv"));
	glMaterialfv(face,pname,params);
}
glMaterialfvCallback glMaterialfv = glMaterialfvDispatcher;

void glMaterialiDispatcher(GLenum face,GLenum pname,GLint param){
	glMateriali = reinterpret_cast<glMaterialiCallback>(OpenGLGetProcAddress("glMateriali"));
	glMateriali(face,pname,param);
}
glMaterialiCallback glMateriali = glMaterialiDispatcher;

void glMaterialivDispatcher(GLenum face,GLenum pname,const GLint * params){
	glMaterialiv = reinterpret_cast<glMaterialivCallback>(OpenGLGetProcAddress("glMaterialiv"));
	glMaterialiv(face,pname,params);
}
glMaterialivCallback glMaterialiv = glMaterialivDispatcher;

void glMatrixModeDispatcher(GLenum mode){
	glMatrixMode = reinterpret_cast<glMatrixModeCallback>(OpenGLGetProcAddress("glMatrixMode"));
	glMatrixMode(mode);
}
glMatrixModeCallback glMatrixMode = glMatrixModeDispatcher;

void glMemoryBarrierDispatcher(GLbitfield barriers){
	glMemoryBarrier = reinterpret_cast<glMemoryBarrierCallback>(OpenGLGetProcAddress("glMemoryBarrier"));
	glMemoryBarrier(barriers);
}
glMemoryBarrierCallback glMemoryBarrier = glMemoryBarrierDispatcher;

void glMemoryBarrierByRegionDispatcher(GLbitfield barriers){
	glMemoryBarrierByRegion = reinterpret_cast<glMemoryBarrierByRegionCallback>(OpenGLGetProcAddress("glMemoryBarrierByRegion"));
	glMemoryBarrierByRegion(barriers);
}
glMemoryBarrierByRegionCallback glMemoryBarrierByRegion = glMemoryBarrierByRegionDispatcher;

void glMinSampleShadingDispatcher(GLfloat value){
	glMinSampleShading = reinterpret_cast<glMinSampleShadingCallback>(OpenGLGetProcAddress("glMinSampleShading"));
	glMinSampleShading(value);
}
glMinSampleShadingCallback glMinSampleShading = glMinSampleShadingDispatcher;

void glMultMatrixdDispatcher(const GLdouble * m){
	glMultMatrixd = reinterpret_cast<glMultMatrixdCallback>(OpenGLGetProcAddress("glMultMatrixd"));
	glMultMatrixd(m);
}
glMultMatrixdCallback glMultMatrixd = glMultMatrixdDispatcher;

void glMultMatrixfDispatcher(const GLfloat * m){
	glMultMatrixf = reinterpret_cast<glMultMatrixfCallback>(OpenGLGetProcAddress("glMultMatrixf"));
	glMultMatrixf(m);
}
glMultMatrixfCallback glMultMatrixf = glMultMatrixfDispatcher;

void glMultTransposeMatrixdDispatcher(const GLdouble * m){
	glMultTransposeMatrixd = reinterpret_cast<glMultTransposeMatrixdCallback>(OpenGLGetProcAddress("glMultTransposeMatrixd"));
	glMultTransposeMatrixd(m);
}
glMultTransposeMatrixdCallback glMultTransposeMatrixd = glMultTransposeMatrixdDispatcher;

void glMultTransposeMatrixfDispatcher(const GLfloat * m){
	glMultTransposeMatrixf = reinterpret_cast<glMultTransposeMatrixfCallback>(OpenGLGetProcAddress("glMultTransposeMatrixf"));
	glMultTransposeMatrixf(m);
}
glMultTransposeMatrixfCallback glMultTransposeMatrixf = glMultTransposeMatrixfDispatcher;

void glMultiDrawArraysDispatcher(GLenum mode,const GLint * first,const GLsizei * count,GLsizei drawcount){
	glMultiDrawArrays = reinterpret_cast<glMultiDrawArraysCallback>(OpenGLGetProcAddress("glMultiDrawArrays"));
	glMultiDrawArrays(mode,first,count,drawcount);
}
glMultiDrawArraysCallback glMultiDrawArrays = glMultiDrawArraysDispatcher;

void glMultiDrawArraysIndirectDispatcher(GLenum mode,const void * indirect,GLsizei drawcount,GLsizei stride){
	glMultiDrawArraysIndirect = reinterpret_cast<glMultiDrawArraysIndirectCallback>(OpenGLGetProcAddress("glMultiDrawArraysIndirect"));
	glMultiDrawArraysIndirect(mode,indirect,drawcount,stride);
}
glMultiDrawArraysIndirectCallback glMultiDrawArraysIndirect = glMultiDrawArraysIndirectDispatcher;

void glMultiDrawElementsDispatcher(GLenum mode,const GLsizei * count,GLenum type,const void *const* indices,GLsizei drawcount){
	glMultiDrawElements = reinterpret_cast<glMultiDrawElementsCallback>(OpenGLGetProcAddress("glMultiDrawElements"));
	glMultiDrawElements(mode,count,type,indices,drawcount);
}
glMultiDrawElementsCallback glMultiDrawElements = glMultiDrawElementsDispatcher;

void glMultiDrawElementsBaseVertexDispatcher(GLenum mode,const GLsizei * count,GLenum type,const void *const* indices,GLsizei drawcount,const GLint * basevertex){
	glMultiDrawElementsBaseVertex = reinterpret_cast<glMultiDrawElementsBaseVertexCallback>(OpenGLGetProcAddress("glMultiDrawElementsBaseVertex"));
	glMultiDrawElementsBaseVertex(mode,count,type,indices,drawcount,basevertex);
}
glMultiDrawElementsBaseVertexCallback glMultiDrawElementsBaseVertex = glMultiDrawElementsBaseVertexDispatcher;

void glMultiDrawElementsIndirectDispatcher(GLenum mode,GLenum type,const void * indirect,GLsizei drawcount,GLsizei stride){
	glMultiDrawElementsIndirect = reinterpret_cast<glMultiDrawElementsIndirectCallback>(OpenGLGetProcAddress("glMultiDrawElementsIndirect"));
	glMultiDrawElementsIndirect(mode,type,indirect,drawcount,stride);
}
glMultiDrawElementsIndirectCallback glMultiDrawElementsIndirect = glMultiDrawElementsIndirectDispatcher;

void glMultiTexCoord1dDispatcher(GLenum target,GLdouble s){
	glMultiTexCoord1d = reinterpret_cast<glMultiTexCoord1dCallback>(OpenGLGetProcAddress("glMultiTexCoord1d"));
	glMultiTexCoord1d(target,s);
}
glMultiTexCoord1dCallback glMultiTexCoord1d = glMultiTexCoord1dDispatcher;

void glMultiTexCoord1dvDispatcher(GLenum target,const GLdouble * v){
	glMultiTexCoord1dv = reinterpret_cast<glMultiTexCoord1dvCallback>(OpenGLGetProcAddress("glMultiTexCoord1dv"));
	glMultiTexCoord1dv(target,v);
}
glMultiTexCoord1dvCallback glMultiTexCoord1dv = glMultiTexCoord1dvDispatcher;

void glMultiTexCoord1fDispatcher(GLenum target,GLfloat s){
	glMultiTexCoord1f = reinterpret_cast<glMultiTexCoord1fCallback>(OpenGLGetProcAddress("glMultiTexCoord1f"));
	glMultiTexCoord1f(target,s);
}
glMultiTexCoord1fCallback glMultiTexCoord1f = glMultiTexCoord1fDispatcher;

void glMultiTexCoord1fvDispatcher(GLenum target,const GLfloat * v){
	glMultiTexCoord1fv = reinterpret_cast<glMultiTexCoord1fvCallback>(OpenGLGetProcAddress("glMultiTexCoord1fv"));
	glMultiTexCoord1fv(target,v);
}
glMultiTexCoord1fvCallback glMultiTexCoord1fv = glMultiTexCoord1fvDispatcher;

void glMultiTexCoord1iDispatcher(GLenum target,GLint s){
	glMultiTexCoord1i = reinterpret_cast<glMultiTexCoord1iCallback>(OpenGLGetProcAddress("glMultiTexCoord1i"));
	glMultiTexCoord1i(target,s);
}
glMultiTexCoord1iCallback glMultiTexCoord1i = glMultiTexCoord1iDispatcher;

void glMultiTexCoord1ivDispatcher(GLenum target,const GLint * v){
	glMultiTexCoord1iv = reinterpret_cast<glMultiTexCoord1ivCallback>(OpenGLGetProcAddress("glMultiTexCoord1iv"));
	glMultiTexCoord1iv(target,v);
}
glMultiTexCoord1ivCallback glMultiTexCoord1iv = glMultiTexCoord1ivDispatcher;

void glMultiTexCoord1sDispatcher(GLenum target,GLshort s){
	glMultiTexCoord1s = reinterpret_cast<glMultiTexCoord1sCallback>(OpenGLGetProcAddress("glMultiTexCoord1s"));
	glMultiTexCoord1s(target,s);
}
glMultiTexCoord1sCallback glMultiTexCoord1s = glMultiTexCoord1sDispatcher;

void glMultiTexCoord1svDispatcher(GLenum target,const GLshort * v){
	glMultiTexCoord1sv = reinterpret_cast<glMultiTexCoord1svCallback>(OpenGLGetProcAddress("glMultiTexCoord1sv"));
	glMultiTexCoord1sv(target,v);
}
glMultiTexCoord1svCallback glMultiTexCoord1sv = glMultiTexCoord1svDispatcher;

void glMultiTexCoord2dDispatcher(GLenum target,GLdouble s,GLdouble t){
	glMultiTexCoord2d = reinterpret_cast<glMultiTexCoord2dCallback>(OpenGLGetProcAddress("glMultiTexCoord2d"));
	glMultiTexCoord2d(target,s,t);
}
glMultiTexCoord2dCallback glMultiTexCoord2d = glMultiTexCoord2dDispatcher;

void glMultiTexCoord2dvDispatcher(GLenum target,const GLdouble * v){
	glMultiTexCoord2dv = reinterpret_cast<glMultiTexCoord2dvCallback>(OpenGLGetProcAddress("glMultiTexCoord2dv"));
	glMultiTexCoord2dv(target,v);
}
glMultiTexCoord2dvCallback glMultiTexCoord2dv = glMultiTexCoord2dvDispatcher;

void glMultiTexCoord2fDispatcher(GLenum target,GLfloat s,GLfloat t){
	glMultiTexCoord2f = reinterpret_cast<glMultiTexCoord2fCallback>(OpenGLGetProcAddress("glMultiTexCoord2f"));
	glMultiTexCoord2f(target,s,t);
}
glMultiTexCoord2fCallback glMultiTexCoord2f = glMultiTexCoord2fDispatcher;

void glMultiTexCoord2fvDispatcher(GLenum target,const GLfloat * v){
	glMultiTexCoord2fv = reinterpret_cast<glMultiTexCoord2fvCallback>(OpenGLGetProcAddress("glMultiTexCoord2fv"));
	glMultiTexCoord2fv(target,v);
}
glMultiTexCoord2fvCallback glMultiTexCoord2fv = glMultiTexCoord2fvDispatcher;

void glMultiTexCoord2iDispatcher(GLenum target,GLint s,GLint t){
	glMultiTexCoord2i = reinterpret_cast<glMultiTexCoord2iCallback>(OpenGLGetProcAddress("glMultiTexCoord2i"));
	glMultiTexCoord2i(target,s,t);
}
glMultiTexCoord2iCallback glMultiTexCoord2i = glMultiTexCoord2iDispatcher;

void glMultiTexCoord2ivDispatcher(GLenum target,const GLint * v){
	glMultiTexCoord2iv = reinterpret_cast<glMultiTexCoord2ivCallback>(OpenGLGetProcAddress("glMultiTexCoord2iv"));
	glMultiTexCoord2iv(target,v);
}
glMultiTexCoord2ivCallback glMultiTexCoord2iv = glMultiTexCoord2ivDispatcher;

void glMultiTexCoord2sDispatcher(GLenum target,GLshort s,GLshort t){
	glMultiTexCoord2s = reinterpret_cast<glMultiTexCoord2sCallback>(OpenGLGetProcAddress("glMultiTexCoord2s"));
	glMultiTexCoord2s(target,s,t);
}
glMultiTexCoord2sCallback glMultiTexCoord2s = glMultiTexCoord2sDispatcher;

void glMultiTexCoord2svDispatcher(GLenum target,const GLshort * v){
	glMultiTexCoord2sv = reinterpret_cast<glMultiTexCoord2svCallback>(OpenGLGetProcAddress("glMultiTexCoord2sv"));
	glMultiTexCoord2sv(target,v);
}
glMultiTexCoord2svCallback glMultiTexCoord2sv = glMultiTexCoord2svDispatcher;

void glMultiTexCoord3dDispatcher(GLenum target,GLdouble s,GLdouble t,GLdouble r){
	glMultiTexCoord3d = reinterpret_cast<glMultiTexCoord3dCallback>(OpenGLGetProcAddress("glMultiTexCoord3d"));
	glMultiTexCoord3d(target,s,t,r);
}
glMultiTexCoord3dCallback glMultiTexCoord3d = glMultiTexCoord3dDispatcher;

void glMultiTexCoord3dvDispatcher(GLenum target,const GLdouble * v){
	glMultiTexCoord3dv = reinterpret_cast<glMultiTexCoord3dvCallback>(OpenGLGetProcAddress("glMultiTexCoord3dv"));
	glMultiTexCoord3dv(target,v);
}
glMultiTexCoord3dvCallback glMultiTexCoord3dv = glMultiTexCoord3dvDispatcher;

void glMultiTexCoord3fDispatcher(GLenum target,GLfloat s,GLfloat t,GLfloat r){
	glMultiTexCoord3f = reinterpret_cast<glMultiTexCoord3fCallback>(OpenGLGetProcAddress("glMultiTexCoord3f"));
	glMultiTexCoord3f(target,s,t,r);
}
glMultiTexCoord3fCallback glMultiTexCoord3f = glMultiTexCoord3fDispatcher;

void glMultiTexCoord3fvDispatcher(GLenum target,const GLfloat * v){
	glMultiTexCoord3fv = reinterpret_cast<glMultiTexCoord3fvCallback>(OpenGLGetProcAddress("glMultiTexCoord3fv"));
	glMultiTexCoord3fv(target,v);
}
glMultiTexCoord3fvCallback glMultiTexCoord3fv = glMultiTexCoord3fvDispatcher;

void glMultiTexCoord3iDispatcher(GLenum target,GLint s,GLint t,GLint r){
	glMultiTexCoord3i = reinterpret_cast<glMultiTexCoord3iCallback>(OpenGLGetProcAddress("glMultiTexCoord3i"));
	glMultiTexCoord3i(target,s,t,r);
}
glMultiTexCoord3iCallback glMultiTexCoord3i = glMultiTexCoord3iDispatcher;

void glMultiTexCoord3ivDispatcher(GLenum target,const GLint * v){
	glMultiTexCoord3iv = reinterpret_cast<glMultiTexCoord3ivCallback>(OpenGLGetProcAddress("glMultiTexCoord3iv"));
	glMultiTexCoord3iv(target,v);
}
glMultiTexCoord3ivCallback glMultiTexCoord3iv = glMultiTexCoord3ivDispatcher;

void glMultiTexCoord3sDispatcher(GLenum target,GLshort s,GLshort t,GLshort r){
	glMultiTexCoord3s = reinterpret_cast<glMultiTexCoord3sCallback>(OpenGLGetProcAddress("glMultiTexCoord3s"));
	glMultiTexCoord3s(target,s,t,r);
}
glMultiTexCoord3sCallback glMultiTexCoord3s = glMultiTexCoord3sDispatcher;

void glMultiTexCoord3svDispatcher(GLenum target,const GLshort * v){
	glMultiTexCoord3sv = reinterpret_cast<glMultiTexCoord3svCallback>(OpenGLGetProcAddress("glMultiTexCoord3sv"));
	glMultiTexCoord3sv(target,v);
}
glMultiTexCoord3svCallback glMultiTexCoord3sv = glMultiTexCoord3svDispatcher;

void glMultiTexCoord4dDispatcher(GLenum target,GLdouble s,GLdouble t,GLdouble r,GLdouble q){
	glMultiTexCoord4d = reinterpret_cast<glMultiTexCoord4dCallback>(OpenGLGetProcAddress("glMultiTexCoord4d"));
	glMultiTexCoord4d(target,s,t,r,q);
}
glMultiTexCoord4dCallback glMultiTexCoord4d = glMultiTexCoord4dDispatcher;

void glMultiTexCoord4dvDispatcher(GLenum target,const GLdouble * v){
	glMultiTexCoord4dv = reinterpret_cast<glMultiTexCoord4dvCallback>(OpenGLGetProcAddress("glMultiTexCoord4dv"));
	glMultiTexCoord4dv(target,v);
}
glMultiTexCoord4dvCallback glMultiTexCoord4dv = glMultiTexCoord4dvDispatcher;

void glMultiTexCoord4fDispatcher(GLenum target,GLfloat s,GLfloat t,GLfloat r,GLfloat q){
	glMultiTexCoord4f = reinterpret_cast<glMultiTexCoord4fCallback>(OpenGLGetProcAddress("glMultiTexCoord4f"));
	glMultiTexCoord4f(target,s,t,r,q);
}
glMultiTexCoord4fCallback glMultiTexCoord4f = glMultiTexCoord4fDispatcher;

void glMultiTexCoord4fvDispatcher(GLenum target,const GLfloat * v){
	glMultiTexCoord4fv = reinterpret_cast<glMultiTexCoord4fvCallback>(OpenGLGetProcAddress("glMultiTexCoord4fv"));
	glMultiTexCoord4fv(target,v);
}
glMultiTexCoord4fvCallback glMultiTexCoord4fv = glMultiTexCoord4fvDispatcher;

void glMultiTexCoord4iDispatcher(GLenum target,GLint s,GLint t,GLint r,GLint q){
	glMultiTexCoord4i = reinterpret_cast<glMultiTexCoord4iCallback>(OpenGLGetProcAddress("glMultiTexCoord4i"));
	glMultiTexCoord4i(target,s,t,r,q);
}
glMultiTexCoord4iCallback glMultiTexCoord4i = glMultiTexCoord4iDispatcher;

void glMultiTexCoord4ivDispatcher(GLenum target,const GLint * v){
	glMultiTexCoord4iv = reinterpret_cast<glMultiTexCoord4ivCallback>(OpenGLGetProcAddress("glMultiTexCoord4iv"));
	glMultiTexCoord4iv(target,v);
}
glMultiTexCoord4ivCallback glMultiTexCoord4iv = glMultiTexCoord4ivDispatcher;

void glMultiTexCoord4sDispatcher(GLenum target,GLshort s,GLshort t,GLshort r,GLshort q){
	glMultiTexCoord4s = reinterpret_cast<glMultiTexCoord4sCallback>(OpenGLGetProcAddress("glMultiTexCoord4s"));
	glMultiTexCoord4s(target,s,t,r,q);
}
glMultiTexCoord4sCallback glMultiTexCoord4s = glMultiTexCoord4sDispatcher;

void glMultiTexCoord4svDispatcher(GLenum target,const GLshort * v){
	glMultiTexCoord4sv = reinterpret_cast<glMultiTexCoord4svCallback>(OpenGLGetProcAddress("glMultiTexCoord4sv"));
	glMultiTexCoord4sv(target,v);
}
glMultiTexCoord4svCallback glMultiTexCoord4sv = glMultiTexCoord4svDispatcher;

void glMultiTexCoordP1uiDispatcher(GLenum texture,GLenum type,GLuint coords){
	glMultiTexCoordP1ui = reinterpret_cast<glMultiTexCoordP1uiCallback>(OpenGLGetProcAddress("glMultiTexCoordP1ui"));
	glMultiTexCoordP1ui(texture,type,coords);
}
glMultiTexCoordP1uiCallback glMultiTexCoordP1ui = glMultiTexCoordP1uiDispatcher;

void glMultiTexCoordP1uivDispatcher(GLenum texture,GLenum type,const GLuint * coords){
	glMultiTexCoordP1uiv = reinterpret_cast<glMultiTexCoordP1uivCallback>(OpenGLGetProcAddress("glMultiTexCoordP1uiv"));
	glMultiTexCoordP1uiv(texture,type,coords);
}
glMultiTexCoordP1uivCallback glMultiTexCoordP1uiv = glMultiTexCoordP1uivDispatcher;

void glMultiTexCoordP2uiDispatcher(GLenum texture,GLenum type,GLuint coords){
	glMultiTexCoordP2ui = reinterpret_cast<glMultiTexCoordP2uiCallback>(OpenGLGetProcAddress("glMultiTexCoordP2ui"));
	glMultiTexCoordP2ui(texture,type,coords);
}
glMultiTexCoordP2uiCallback glMultiTexCoordP2ui = glMultiTexCoordP2uiDispatcher;

void glMultiTexCoordP2uivDispatcher(GLenum texture,GLenum type,const GLuint * coords){
	glMultiTexCoordP2uiv = reinterpret_cast<glMultiTexCoordP2uivCallback>(OpenGLGetProcAddress("glMultiTexCoordP2uiv"));
	glMultiTexCoordP2uiv(texture,type,coords);
}
glMultiTexCoordP2uivCallback glMultiTexCoordP2uiv = glMultiTexCoordP2uivDispatcher;

void glMultiTexCoordP3uiDispatcher(GLenum texture,GLenum type,GLuint coords){
	glMultiTexCoordP3ui = reinterpret_cast<glMultiTexCoordP3uiCallback>(OpenGLGetProcAddress("glMultiTexCoordP3ui"));
	glMultiTexCoordP3ui(texture,type,coords);
}
glMultiTexCoordP3uiCallback glMultiTexCoordP3ui = glMultiTexCoordP3uiDispatcher;

void glMultiTexCoordP3uivDispatcher(GLenum texture,GLenum type,const GLuint * coords){
	glMultiTexCoordP3uiv = reinterpret_cast<glMultiTexCoordP3uivCallback>(OpenGLGetProcAddress("glMultiTexCoordP3uiv"));
	glMultiTexCoordP3uiv(texture,type,coords);
}
glMultiTexCoordP3uivCallback glMultiTexCoordP3uiv = glMultiTexCoordP3uivDispatcher;

void glMultiTexCoordP4uiDispatcher(GLenum texture,GLenum type,GLuint coords){
	glMultiTexCoordP4ui = reinterpret_cast<glMultiTexCoordP4uiCallback>(OpenGLGetProcAddress("glMultiTexCoordP4ui"));
	glMultiTexCoordP4ui(texture,type,coords);
}
glMultiTexCoordP4uiCallback glMultiTexCoordP4ui = glMultiTexCoordP4uiDispatcher;

void glMultiTexCoordP4uivDispatcher(GLenum texture,GLenum type,const GLuint * coords){
	glMultiTexCoordP4uiv = reinterpret_cast<glMultiTexCoordP4uivCallback>(OpenGLGetProcAddress("glMultiTexCoordP4uiv"));
	glMultiTexCoordP4uiv(texture,type,coords);
}
glMultiTexCoordP4uivCallback glMultiTexCoordP4uiv = glMultiTexCoordP4uivDispatcher;

void glNamedBufferDataDispatcher(GLuint buffer,GLsizei size,const void * data,GLenum usage){
	glNamedBufferData = reinterpret_cast<glNamedBufferDataCallback>(OpenGLGetProcAddress("glNamedBufferData"));
	glNamedBufferData(buffer,size,data,usage);
}
glNamedBufferDataCallback glNamedBufferData = glNamedBufferDataDispatcher;

void glNamedBufferStorageDispatcher(GLuint buffer,GLsizei size,const void * data,GLbitfield flags){
	glNamedBufferStorage = reinterpret_cast<glNamedBufferStorageCallback>(OpenGLGetProcAddress("glNamedBufferStorage"));
	glNamedBufferStorage(buffer,size,data,flags);
}
glNamedBufferStorageCallback glNamedBufferStorage = glNamedBufferStorageDispatcher;

void glNamedBufferSubDataDispatcher(GLuint buffer,GLintptr offset,GLsizei size,const void * data){
	glNamedBufferSubData = reinterpret_cast<glNamedBufferSubDataCallback>(OpenGLGetProcAddress("glNamedBufferSubData"));
	glNamedBufferSubData(buffer,offset,size,data);
}
glNamedBufferSubDataCallback glNamedBufferSubData = glNamedBufferSubDataDispatcher;

void glNamedFramebufferDrawBufferDispatcher(GLuint framebuffer,GLenum buf){
	glNamedFramebufferDrawBuffer = reinterpret_cast<glNamedFramebufferDrawBufferCallback>(OpenGLGetProcAddress("glNamedFramebufferDrawBuffer"));
	glNamedFramebufferDrawBuffer(framebuffer,buf);
}
glNamedFramebufferDrawBufferCallback glNamedFramebufferDrawBuffer = glNamedFramebufferDrawBufferDispatcher;

void glNamedFramebufferDrawBuffersDispatcher(GLuint framebuffer,GLsizei n,const GLenum * bufs){
	glNamedFramebufferDrawBuffers = reinterpret_cast<glNamedFramebufferDrawBuffersCallback>(OpenGLGetProcAddress("glNamedFramebufferDrawBuffers"));
	glNamedFramebufferDrawBuffers(framebuffer,n,bufs);
}
glNamedFramebufferDrawBuffersCallback glNamedFramebufferDrawBuffers = glNamedFramebufferDrawBuffersDispatcher;

void glNamedFramebufferParameteriDispatcher(GLuint framebuffer,GLenum pname,GLint param){
	glNamedFramebufferParameteri = reinterpret_cast<glNamedFramebufferParameteriCallback>(OpenGLGetProcAddress("glNamedFramebufferParameteri"));
	glNamedFramebufferParameteri(framebuffer,pname,param);
}
glNamedFramebufferParameteriCallback glNamedFramebufferParameteri = glNamedFramebufferParameteriDispatcher;

void glNamedFramebufferReadBufferDispatcher(GLuint framebuffer,GLenum src){
	glNamedFramebufferReadBuffer = reinterpret_cast<glNamedFramebufferReadBufferCallback>(OpenGLGetProcAddress("glNamedFramebufferReadBuffer"));
	glNamedFramebufferReadBuffer(framebuffer,src);
}
glNamedFramebufferReadBufferCallback glNamedFramebufferReadBuffer = glNamedFramebufferReadBufferDispatcher;

void glNamedFramebufferRenderbufferDispatcher(GLuint framebuffer,GLenum attachment,GLenum renderbuffertarget,GLuint renderbuffer){
	glNamedFramebufferRenderbuffer = reinterpret_cast<glNamedFramebufferRenderbufferCallback>(OpenGLGetProcAddress("glNamedFramebufferRenderbuffer"));
	glNamedFramebufferRenderbuffer(framebuffer,attachment,renderbuffertarget,renderbuffer);
}
glNamedFramebufferRenderbufferCallback glNamedFramebufferRenderbuffer = glNamedFramebufferRenderbufferDispatcher;

void glNamedFramebufferTextureDispatcher(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level){
	glNamedFramebufferTexture = reinterpret_cast<glNamedFramebufferTextureCallback>(OpenGLGetProcAddress("glNamedFramebufferTexture"));
	glNamedFramebufferTexture(framebuffer,attachment,texture,level);
}
glNamedFramebufferTextureCallback glNamedFramebufferTexture = glNamedFramebufferTextureDispatcher;

void glNamedFramebufferTextureLayerDispatcher(GLuint framebuffer,GLenum attachment,GLuint texture,GLint level,GLint layer){
	glNamedFramebufferTextureLayer = reinterpret_cast<glNamedFramebufferTextureLayerCallback>(OpenGLGetProcAddress("glNamedFramebufferTextureLayer"));
	glNamedFramebufferTextureLayer(framebuffer,attachment,texture,level,layer);
}
glNamedFramebufferTextureLayerCallback glNamedFramebufferTextureLayer = glNamedFramebufferTextureLayerDispatcher;

void glNamedRenderbufferStorageDispatcher(GLuint renderbuffer,GLenum internalformat,GLsizei width,GLsizei height){
	glNamedRenderbufferStorage = reinterpret_cast<glNamedRenderbufferStorageCallback>(OpenGLGetProcAddress("glNamedRenderbufferStorage"));
	glNamedRenderbufferStorage(renderbuffer,internalformat,width,height);
}
glNamedRenderbufferStorageCallback glNamedRenderbufferStorage = glNamedRenderbufferStorageDispatcher;

void glNamedRenderbufferStorageMultisampleDispatcher(GLuint renderbuffer,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height){
	glNamedRenderbufferStorageMultisample = reinterpret_cast<glNamedRenderbufferStorageMultisampleCallback>(OpenGLGetProcAddress("glNamedRenderbufferStorageMultisample"));
	glNamedRenderbufferStorageMultisample(renderbuffer,samples,internalformat,width,height);
}
glNamedRenderbufferStorageMultisampleCallback glNamedRenderbufferStorageMultisample = glNamedRenderbufferStorageMultisampleDispatcher;

void glNewListDispatcher(GLuint list,GLenum mode){
	glNewList = reinterpret_cast<glNewListCallback>(OpenGLGetProcAddress("glNewList"));
	glNewList(list,mode);
}
glNewListCallback glNewList = glNewListDispatcher;

void glNormal3bDispatcher(GLbyte nx,GLbyte ny,GLbyte nz){
	glNormal3b = reinterpret_cast<glNormal3bCallback>(OpenGLGetProcAddress("glNormal3b"));
	glNormal3b(nx,ny,nz);
}
glNormal3bCallback glNormal3b = glNormal3bDispatcher;

void glNormal3bvDispatcher(const GLbyte * v){
	glNormal3bv = reinterpret_cast<glNormal3bvCallback>(OpenGLGetProcAddress("glNormal3bv"));
	glNormal3bv(v);
}
glNormal3bvCallback glNormal3bv = glNormal3bvDispatcher;

void glNormal3dDispatcher(GLdouble nx,GLdouble ny,GLdouble nz){
	glNormal3d = reinterpret_cast<glNormal3dCallback>(OpenGLGetProcAddress("glNormal3d"));
	glNormal3d(nx,ny,nz);
}
glNormal3dCallback glNormal3d = glNormal3dDispatcher;

void glNormal3dvDispatcher(const GLdouble * v){
	glNormal3dv = reinterpret_cast<glNormal3dvCallback>(OpenGLGetProcAddress("glNormal3dv"));
	glNormal3dv(v);
}
glNormal3dvCallback glNormal3dv = glNormal3dvDispatcher;

void glNormal3fDispatcher(GLfloat nx,GLfloat ny,GLfloat nz){
	glNormal3f = reinterpret_cast<glNormal3fCallback>(OpenGLGetProcAddress("glNormal3f"));
	glNormal3f(nx,ny,nz);
}
glNormal3fCallback glNormal3f = glNormal3fDispatcher;

void glNormal3fvDispatcher(const GLfloat * v){
	glNormal3fv = reinterpret_cast<glNormal3fvCallback>(OpenGLGetProcAddress("glNormal3fv"));
	glNormal3fv(v);
}
glNormal3fvCallback glNormal3fv = glNormal3fvDispatcher;

void glNormal3iDispatcher(GLint nx,GLint ny,GLint nz){
	glNormal3i = reinterpret_cast<glNormal3iCallback>(OpenGLGetProcAddress("glNormal3i"));
	glNormal3i(nx,ny,nz);
}
glNormal3iCallback glNormal3i = glNormal3iDispatcher;

void glNormal3ivDispatcher(const GLint * v){
	glNormal3iv = reinterpret_cast<glNormal3ivCallback>(OpenGLGetProcAddress("glNormal3iv"));
	glNormal3iv(v);
}
glNormal3ivCallback glNormal3iv = glNormal3ivDispatcher;

void glNormal3sDispatcher(GLshort nx,GLshort ny,GLshort nz){
	glNormal3s = reinterpret_cast<glNormal3sCallback>(OpenGLGetProcAddress("glNormal3s"));
	glNormal3s(nx,ny,nz);
}
glNormal3sCallback glNormal3s = glNormal3sDispatcher;

void glNormal3svDispatcher(const GLshort * v){
	glNormal3sv = reinterpret_cast<glNormal3svCallback>(OpenGLGetProcAddress("glNormal3sv"));
	glNormal3sv(v);
}
glNormal3svCallback glNormal3sv = glNormal3svDispatcher;

void glNormalP3uiDispatcher(GLenum type,GLuint coords){
	glNormalP3ui = reinterpret_cast<glNormalP3uiCallback>(OpenGLGetProcAddress("glNormalP3ui"));
	glNormalP3ui(type,coords);
}
glNormalP3uiCallback glNormalP3ui = glNormalP3uiDispatcher;

void glNormalP3uivDispatcher(GLenum type,const GLuint * coords){
	glNormalP3uiv = reinterpret_cast<glNormalP3uivCallback>(OpenGLGetProcAddress("glNormalP3uiv"));
	glNormalP3uiv(type,coords);
}
glNormalP3uivCallback glNormalP3uiv = glNormalP3uivDispatcher;

void glNormalPointerDispatcher(GLenum type,GLsizei stride,const void * pointer){
	glNormalPointer = reinterpret_cast<glNormalPointerCallback>(OpenGLGetProcAddress("glNormalPointer"));
	glNormalPointer(type,stride,pointer);
}
glNormalPointerCallback glNormalPointer = glNormalPointerDispatcher;

void glObjectLabelDispatcher(GLenum identifier,GLuint name,GLsizei length,const GLchar * label){
	glObjectLabel = reinterpret_cast<glObjectLabelCallback>(OpenGLGetProcAddress("glObjectLabel"));
	glObjectLabel(identifier,name,length,label);
}
glObjectLabelCallback glObjectLabel = glObjectLabelDispatcher;

void glObjectPtrLabelDispatcher(const void * ptr,GLsizei length,const GLchar * label){
	glObjectPtrLabel = reinterpret_cast<glObjectPtrLabelCallback>(OpenGLGetProcAddress("glObjectPtrLabel"));
	glObjectPtrLabel(ptr,length,label);
}
glObjectPtrLabelCallback glObjectPtrLabel = glObjectPtrLabelDispatcher;

void glOrthoDispatcher(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar){
	glOrtho = reinterpret_cast<glOrthoCallback>(OpenGLGetProcAddress("glOrtho"));
	glOrtho(left,right,bottom,top,zNear,zFar);
}
glOrthoCallback glOrtho = glOrthoDispatcher;

void glPassThroughDispatcher(GLfloat token){
	glPassThrough = reinterpret_cast<glPassThroughCallback>(OpenGLGetProcAddress("glPassThrough"));
	glPassThrough(token);
}
glPassThroughCallback glPassThrough = glPassThroughDispatcher;

void glPatchParameterfvDispatcher(GLenum pname,const GLfloat * values){
	glPatchParameterfv = reinterpret_cast<glPatchParameterfvCallback>(OpenGLGetProcAddress("glPatchParameterfv"));
	glPatchParameterfv(pname,values);
}
glPatchParameterfvCallback glPatchParameterfv = glPatchParameterfvDispatcher;

void glPatchParameteriDispatcher(GLenum pname,GLint value){
	glPatchParameteri = reinterpret_cast<glPatchParameteriCallback>(OpenGLGetProcAddress("glPatchParameteri"));
	glPatchParameteri(pname,value);
}
glPatchParameteriCallback glPatchParameteri = glPatchParameteriDispatcher;

void glPauseTransformFeedbackDispatcher(){
	glPauseTransformFeedback = reinterpret_cast<glPauseTransformFeedbackCallback>(OpenGLGetProcAddress("glPauseTransformFeedback"));
	glPauseTransformFeedback();
}
glPauseTransformFeedbackCallback glPauseTransformFeedback = glPauseTransformFeedbackDispatcher;

void glPixelMapfvDispatcher(GLenum map,GLsizei mapsize,const GLfloat * values){
	glPixelMapfv = reinterpret_cast<glPixelMapfvCallback>(OpenGLGetProcAddress("glPixelMapfv"));
	glPixelMapfv(map,mapsize,values);
}
glPixelMapfvCallback glPixelMapfv = glPixelMapfvDispatcher;

void glPixelMapuivDispatcher(GLenum map,GLsizei mapsize,const GLuint * values){
	glPixelMapuiv = reinterpret_cast<glPixelMapuivCallback>(OpenGLGetProcAddress("glPixelMapuiv"));
	glPixelMapuiv(map,mapsize,values);
}
glPixelMapuivCallback glPixelMapuiv = glPixelMapuivDispatcher;

void glPixelMapusvDispatcher(GLenum map,GLsizei mapsize,const GLushort * values){
	glPixelMapusv = reinterpret_cast<glPixelMapusvCallback>(OpenGLGetProcAddress("glPixelMapusv"));
	glPixelMapusv(map,mapsize,values);
}
glPixelMapusvCallback glPixelMapusv = glPixelMapusvDispatcher;

void glPixelStorefDispatcher(GLenum pname,GLfloat param){
	glPixelStoref = reinterpret_cast<glPixelStorefCallback>(OpenGLGetProcAddress("glPixelStoref"));
	glPixelStoref(pname,param);
}
glPixelStorefCallback glPixelStoref = glPixelStorefDispatcher;

void glPixelStoreiDispatcher(GLenum pname,GLint param){
	glPixelStorei = reinterpret_cast<glPixelStoreiCallback>(OpenGLGetProcAddress("glPixelStorei"));
	glPixelStorei(pname,param);
}
glPixelStoreiCallback glPixelStorei = glPixelStoreiDispatcher;

void glPixelTransferfDispatcher(GLenum pname,GLfloat param){
	glPixelTransferf = reinterpret_cast<glPixelTransferfCallback>(OpenGLGetProcAddress("glPixelTransferf"));
	glPixelTransferf(pname,param);
}
glPixelTransferfCallback glPixelTransferf = glPixelTransferfDispatcher;

void glPixelTransferiDispatcher(GLenum pname,GLint param){
	glPixelTransferi = reinterpret_cast<glPixelTransferiCallback>(OpenGLGetProcAddress("glPixelTransferi"));
	glPixelTransferi(pname,param);
}
glPixelTransferiCallback glPixelTransferi = glPixelTransferiDispatcher;

void glPixelZoomDispatcher(GLfloat xfactor,GLfloat yfactor){
	glPixelZoom = reinterpret_cast<glPixelZoomCallback>(OpenGLGetProcAddress("glPixelZoom"));
	glPixelZoom(xfactor,yfactor);
}
glPixelZoomCallback glPixelZoom = glPixelZoomDispatcher;

void glPointParameterfDispatcher(GLenum pname,GLfloat param){
	glPointParameterf = reinterpret_cast<glPointParameterfCallback>(OpenGLGetProcAddress("glPointParameterf"));
	glPointParameterf(pname,param);
}
glPointParameterfCallback glPointParameterf = glPointParameterfDispatcher;

void glPointParameterfvDispatcher(GLenum pname,const GLfloat * params){
	glPointParameterfv = reinterpret_cast<glPointParameterfvCallback>(OpenGLGetProcAddress("glPointParameterfv"));
	glPointParameterfv(pname,params);
}
glPointParameterfvCallback glPointParameterfv = glPointParameterfvDispatcher;

void glPointParameteriDispatcher(GLenum pname,GLint param){
	glPointParameteri = reinterpret_cast<glPointParameteriCallback>(OpenGLGetProcAddress("glPointParameteri"));
	glPointParameteri(pname,param);
}
glPointParameteriCallback glPointParameteri = glPointParameteriDispatcher;

void glPointParameterivDispatcher(GLenum pname,const GLint * params){
	glPointParameteriv = reinterpret_cast<glPointParameterivCallback>(OpenGLGetProcAddress("glPointParameteriv"));
	glPointParameteriv(pname,params);
}
glPointParameterivCallback glPointParameteriv = glPointParameterivDispatcher;

void glPointSizeDispatcher(GLfloat size){
	glPointSize = reinterpret_cast<glPointSizeCallback>(OpenGLGetProcAddress("glPointSize"));
	glPointSize(size);
}
glPointSizeCallback glPointSize = glPointSizeDispatcher;

void glPolygonModeDispatcher(GLenum face,GLenum mode){
	glPolygonMode = reinterpret_cast<glPolygonModeCallback>(OpenGLGetProcAddress("glPolygonMode"));
	glPolygonMode(face,mode);
}
glPolygonModeCallback glPolygonMode = glPolygonModeDispatcher;

void glPolygonOffsetDispatcher(GLfloat factor,GLfloat units){
	glPolygonOffset = reinterpret_cast<glPolygonOffsetCallback>(OpenGLGetProcAddress("glPolygonOffset"));
	glPolygonOffset(factor,units);
}
glPolygonOffsetCallback glPolygonOffset = glPolygonOffsetDispatcher;

void glPolygonStippleDispatcher(const GLubyte * mask){
	glPolygonStipple = reinterpret_cast<glPolygonStippleCallback>(OpenGLGetProcAddress("glPolygonStipple"));
	glPolygonStipple(mask);
}
glPolygonStippleCallback glPolygonStipple = glPolygonStippleDispatcher;

void glPopAttribDispatcher(){
	glPopAttrib = reinterpret_cast<glPopAttribCallback>(OpenGLGetProcAddress("glPopAttrib"));
	glPopAttrib();
}
glPopAttribCallback glPopAttrib = glPopAttribDispatcher;

void glPopClientAttribDispatcher(){
	glPopClientAttrib = reinterpret_cast<glPopClientAttribCallback>(OpenGLGetProcAddress("glPopClientAttrib"));
	glPopClientAttrib();
}
glPopClientAttribCallback glPopClientAttrib = glPopClientAttribDispatcher;

void glPopDebugGroupDispatcher(){
	glPopDebugGroup = reinterpret_cast<glPopDebugGroupCallback>(OpenGLGetProcAddress("glPopDebugGroup"));
	glPopDebugGroup();
}
glPopDebugGroupCallback glPopDebugGroup = glPopDebugGroupDispatcher;

void glPopMatrixDispatcher(){
	glPopMatrix = reinterpret_cast<glPopMatrixCallback>(OpenGLGetProcAddress("glPopMatrix"));
	glPopMatrix();
}
glPopMatrixCallback glPopMatrix = glPopMatrixDispatcher;

void glPopNameDispatcher(){
	glPopName = reinterpret_cast<glPopNameCallback>(OpenGLGetProcAddress("glPopName"));
	glPopName();
}
glPopNameCallback glPopName = glPopNameDispatcher;

void glPrimitiveRestartIndexDispatcher(GLuint index){
	glPrimitiveRestartIndex = reinterpret_cast<glPrimitiveRestartIndexCallback>(OpenGLGetProcAddress("glPrimitiveRestartIndex"));
	glPrimitiveRestartIndex(index);
}
glPrimitiveRestartIndexCallback glPrimitiveRestartIndex = glPrimitiveRestartIndexDispatcher;

void glPrioritizeTexturesDispatcher(GLsizei n,const GLuint * textures,const GLfloat * priorities){
	glPrioritizeTextures = reinterpret_cast<glPrioritizeTexturesCallback>(OpenGLGetProcAddress("glPrioritizeTextures"));
	glPrioritizeTextures(n,textures,priorities);
}
glPrioritizeTexturesCallback glPrioritizeTextures = glPrioritizeTexturesDispatcher;

void glProgramBinaryDispatcher(GLuint program,GLenum binaryFormat,const void * binary,GLsizei length){
	glProgramBinary = reinterpret_cast<glProgramBinaryCallback>(OpenGLGetProcAddress("glProgramBinary"));
	glProgramBinary(program,binaryFormat,binary,length);
}
glProgramBinaryCallback glProgramBinary = glProgramBinaryDispatcher;

void glProgramParameteriDispatcher(GLuint program,GLenum pname,GLint value){
	glProgramParameteri = reinterpret_cast<glProgramParameteriCallback>(OpenGLGetProcAddress("glProgramParameteri"));
	glProgramParameteri(program,pname,value);
}
glProgramParameteriCallback glProgramParameteri = glProgramParameteriDispatcher;

void glProgramUniform1dDispatcher(GLuint program,GLint location,GLdouble v0){
	glProgramUniform1d = reinterpret_cast<glProgramUniform1dCallback>(OpenGLGetProcAddress("glProgramUniform1d"));
	glProgramUniform1d(program,location,v0);
}
glProgramUniform1dCallback glProgramUniform1d = glProgramUniform1dDispatcher;

void glProgramUniform1dvDispatcher(GLuint program,GLint location,GLsizei count,const GLdouble * value){
	glProgramUniform1dv = reinterpret_cast<glProgramUniform1dvCallback>(OpenGLGetProcAddress("glProgramUniform1dv"));
	glProgramUniform1dv(program,location,count,value);
}
glProgramUniform1dvCallback glProgramUniform1dv = glProgramUniform1dvDispatcher;

void glProgramUniform1fDispatcher(GLuint program,GLint location,GLfloat v0){
	glProgramUniform1f = reinterpret_cast<glProgramUniform1fCallback>(OpenGLGetProcAddress("glProgramUniform1f"));
	glProgramUniform1f(program,location,v0);
}
glProgramUniform1fCallback glProgramUniform1f = glProgramUniform1fDispatcher;

void glProgramUniform1fvDispatcher(GLuint program,GLint location,GLsizei count,const GLfloat * value){
	glProgramUniform1fv = reinterpret_cast<glProgramUniform1fvCallback>(OpenGLGetProcAddress("glProgramUniform1fv"));
	glProgramUniform1fv(program,location,count,value);
}
glProgramUniform1fvCallback glProgramUniform1fv = glProgramUniform1fvDispatcher;

void glProgramUniform1iDispatcher(GLuint program,GLint location,GLint v0){
	glProgramUniform1i = reinterpret_cast<glProgramUniform1iCallback>(OpenGLGetProcAddress("glProgramUniform1i"));
	glProgramUniform1i(program,location,v0);
}
glProgramUniform1iCallback glProgramUniform1i = glProgramUniform1iDispatcher;

void glProgramUniform1ivDispatcher(GLuint program,GLint location,GLsizei count,const GLint * value){
	glProgramUniform1iv = reinterpret_cast<glProgramUniform1ivCallback>(OpenGLGetProcAddress("glProgramUniform1iv"));
	glProgramUniform1iv(program,location,count,value);
}
glProgramUniform1ivCallback glProgramUniform1iv = glProgramUniform1ivDispatcher;

void glProgramUniform1uiDispatcher(GLuint program,GLint location,GLuint v0){
	glProgramUniform1ui = reinterpret_cast<glProgramUniform1uiCallback>(OpenGLGetProcAddress("glProgramUniform1ui"));
	glProgramUniform1ui(program,location,v0);
}
glProgramUniform1uiCallback glProgramUniform1ui = glProgramUniform1uiDispatcher;

void glProgramUniform1uivDispatcher(GLuint program,GLint location,GLsizei count,const GLuint * value){
	glProgramUniform1uiv = reinterpret_cast<glProgramUniform1uivCallback>(OpenGLGetProcAddress("glProgramUniform1uiv"));
	glProgramUniform1uiv(program,location,count,value);
}
glProgramUniform1uivCallback glProgramUniform1uiv = glProgramUniform1uivDispatcher;

void glProgramUniform2dDispatcher(GLuint program,GLint location,GLdouble v0,GLdouble v1){
	glProgramUniform2d = reinterpret_cast<glProgramUniform2dCallback>(OpenGLGetProcAddress("glProgramUniform2d"));
	glProgramUniform2d(program,location,v0,v1);
}
glProgramUniform2dCallback glProgramUniform2d = glProgramUniform2dDispatcher;

void glProgramUniform2dvDispatcher(GLuint program,GLint location,GLsizei count,const GLdouble * value){
	glProgramUniform2dv = reinterpret_cast<glProgramUniform2dvCallback>(OpenGLGetProcAddress("glProgramUniform2dv"));
	glProgramUniform2dv(program,location,count,value);
}
glProgramUniform2dvCallback glProgramUniform2dv = glProgramUniform2dvDispatcher;

void glProgramUniform2fDispatcher(GLuint program,GLint location,GLfloat v0,GLfloat v1){
	glProgramUniform2f = reinterpret_cast<glProgramUniform2fCallback>(OpenGLGetProcAddress("glProgramUniform2f"));
	glProgramUniform2f(program,location,v0,v1);
}
glProgramUniform2fCallback glProgramUniform2f = glProgramUniform2fDispatcher;

void glProgramUniform2fvDispatcher(GLuint program,GLint location,GLsizei count,const GLfloat * value){
	glProgramUniform2fv = reinterpret_cast<glProgramUniform2fvCallback>(OpenGLGetProcAddress("glProgramUniform2fv"));
	glProgramUniform2fv(program,location,count,value);
}
glProgramUniform2fvCallback glProgramUniform2fv = glProgramUniform2fvDispatcher;

void glProgramUniform2iDispatcher(GLuint program,GLint location,GLint v0,GLint v1){
	glProgramUniform2i = reinterpret_cast<glProgramUniform2iCallback>(OpenGLGetProcAddress("glProgramUniform2i"));
	glProgramUniform2i(program,location,v0,v1);
}
glProgramUniform2iCallback glProgramUniform2i = glProgramUniform2iDispatcher;

void glProgramUniform2ivDispatcher(GLuint program,GLint location,GLsizei count,const GLint * value){
	glProgramUniform2iv = reinterpret_cast<glProgramUniform2ivCallback>(OpenGLGetProcAddress("glProgramUniform2iv"));
	glProgramUniform2iv(program,location,count,value);
}
glProgramUniform2ivCallback glProgramUniform2iv = glProgramUniform2ivDispatcher;

void glProgramUniform2uiDispatcher(GLuint program,GLint location,GLuint v0,GLuint v1){
	glProgramUniform2ui = reinterpret_cast<glProgramUniform2uiCallback>(OpenGLGetProcAddress("glProgramUniform2ui"));
	glProgramUniform2ui(program,location,v0,v1);
}
glProgramUniform2uiCallback glProgramUniform2ui = glProgramUniform2uiDispatcher;

void glProgramUniform2uivDispatcher(GLuint program,GLint location,GLsizei count,const GLuint * value){
	glProgramUniform2uiv = reinterpret_cast<glProgramUniform2uivCallback>(OpenGLGetProcAddress("glProgramUniform2uiv"));
	glProgramUniform2uiv(program,location,count,value);
}
glProgramUniform2uivCallback glProgramUniform2uiv = glProgramUniform2uivDispatcher;

void glProgramUniform3dDispatcher(GLuint program,GLint location,GLdouble v0,GLdouble v1,GLdouble v2){
	glProgramUniform3d = reinterpret_cast<glProgramUniform3dCallback>(OpenGLGetProcAddress("glProgramUniform3d"));
	glProgramUniform3d(program,location,v0,v1,v2);
}
glProgramUniform3dCallback glProgramUniform3d = glProgramUniform3dDispatcher;

void glProgramUniform3dvDispatcher(GLuint program,GLint location,GLsizei count,const GLdouble * value){
	glProgramUniform3dv = reinterpret_cast<glProgramUniform3dvCallback>(OpenGLGetProcAddress("glProgramUniform3dv"));
	glProgramUniform3dv(program,location,count,value);
}
glProgramUniform3dvCallback glProgramUniform3dv = glProgramUniform3dvDispatcher;

void glProgramUniform3fDispatcher(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2){
	glProgramUniform3f = reinterpret_cast<glProgramUniform3fCallback>(OpenGLGetProcAddress("glProgramUniform3f"));
	glProgramUniform3f(program,location,v0,v1,v2);
}
glProgramUniform3fCallback glProgramUniform3f = glProgramUniform3fDispatcher;

void glProgramUniform3fvDispatcher(GLuint program,GLint location,GLsizei count,const GLfloat * value){
	glProgramUniform3fv = reinterpret_cast<glProgramUniform3fvCallback>(OpenGLGetProcAddress("glProgramUniform3fv"));
	glProgramUniform3fv(program,location,count,value);
}
glProgramUniform3fvCallback glProgramUniform3fv = glProgramUniform3fvDispatcher;

void glProgramUniform3iDispatcher(GLuint program,GLint location,GLint v0,GLint v1,GLint v2){
	glProgramUniform3i = reinterpret_cast<glProgramUniform3iCallback>(OpenGLGetProcAddress("glProgramUniform3i"));
	glProgramUniform3i(program,location,v0,v1,v2);
}
glProgramUniform3iCallback glProgramUniform3i = glProgramUniform3iDispatcher;

void glProgramUniform3ivDispatcher(GLuint program,GLint location,GLsizei count,const GLint * value){
	glProgramUniform3iv = reinterpret_cast<glProgramUniform3ivCallback>(OpenGLGetProcAddress("glProgramUniform3iv"));
	glProgramUniform3iv(program,location,count,value);
}
glProgramUniform3ivCallback glProgramUniform3iv = glProgramUniform3ivDispatcher;

void glProgramUniform3uiDispatcher(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2){
	glProgramUniform3ui = reinterpret_cast<glProgramUniform3uiCallback>(OpenGLGetProcAddress("glProgramUniform3ui"));
	glProgramUniform3ui(program,location,v0,v1,v2);
}
glProgramUniform3uiCallback glProgramUniform3ui = glProgramUniform3uiDispatcher;

void glProgramUniform3uivDispatcher(GLuint program,GLint location,GLsizei count,const GLuint * value){
	glProgramUniform3uiv = reinterpret_cast<glProgramUniform3uivCallback>(OpenGLGetProcAddress("glProgramUniform3uiv"));
	glProgramUniform3uiv(program,location,count,value);
}
glProgramUniform3uivCallback glProgramUniform3uiv = glProgramUniform3uivDispatcher;

void glProgramUniform4dDispatcher(GLuint program,GLint location,GLdouble v0,GLdouble v1,GLdouble v2,GLdouble v3){
	glProgramUniform4d = reinterpret_cast<glProgramUniform4dCallback>(OpenGLGetProcAddress("glProgramUniform4d"));
	glProgramUniform4d(program,location,v0,v1,v2,v3);
}
glProgramUniform4dCallback glProgramUniform4d = glProgramUniform4dDispatcher;

void glProgramUniform4dvDispatcher(GLuint program,GLint location,GLsizei count,const GLdouble * value){
	glProgramUniform4dv = reinterpret_cast<glProgramUniform4dvCallback>(OpenGLGetProcAddress("glProgramUniform4dv"));
	glProgramUniform4dv(program,location,count,value);
}
glProgramUniform4dvCallback glProgramUniform4dv = glProgramUniform4dvDispatcher;

void glProgramUniform4fDispatcher(GLuint program,GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3){
	glProgramUniform4f = reinterpret_cast<glProgramUniform4fCallback>(OpenGLGetProcAddress("glProgramUniform4f"));
	glProgramUniform4f(program,location,v0,v1,v2,v3);
}
glProgramUniform4fCallback glProgramUniform4f = glProgramUniform4fDispatcher;

void glProgramUniform4fvDispatcher(GLuint program,GLint location,GLsizei count,const GLfloat * value){
	glProgramUniform4fv = reinterpret_cast<glProgramUniform4fvCallback>(OpenGLGetProcAddress("glProgramUniform4fv"));
	glProgramUniform4fv(program,location,count,value);
}
glProgramUniform4fvCallback glProgramUniform4fv = glProgramUniform4fvDispatcher;

void glProgramUniform4iDispatcher(GLuint program,GLint location,GLint v0,GLint v1,GLint v2,GLint v3){
	glProgramUniform4i = reinterpret_cast<glProgramUniform4iCallback>(OpenGLGetProcAddress("glProgramUniform4i"));
	glProgramUniform4i(program,location,v0,v1,v2,v3);
}
glProgramUniform4iCallback glProgramUniform4i = glProgramUniform4iDispatcher;

void glProgramUniform4ivDispatcher(GLuint program,GLint location,GLsizei count,const GLint * value){
	glProgramUniform4iv = reinterpret_cast<glProgramUniform4ivCallback>(OpenGLGetProcAddress("glProgramUniform4iv"));
	glProgramUniform4iv(program,location,count,value);
}
glProgramUniform4ivCallback glProgramUniform4iv = glProgramUniform4ivDispatcher;

void glProgramUniform4uiDispatcher(GLuint program,GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3){
	glProgramUniform4ui = reinterpret_cast<glProgramUniform4uiCallback>(OpenGLGetProcAddress("glProgramUniform4ui"));
	glProgramUniform4ui(program,location,v0,v1,v2,v3);
}
glProgramUniform4uiCallback glProgramUniform4ui = glProgramUniform4uiDispatcher;

void glProgramUniform4uivDispatcher(GLuint program,GLint location,GLsizei count,const GLuint * value){
	glProgramUniform4uiv = reinterpret_cast<glProgramUniform4uivCallback>(OpenGLGetProcAddress("glProgramUniform4uiv"));
	glProgramUniform4uiv(program,location,count,value);
}
glProgramUniform4uivCallback glProgramUniform4uiv = glProgramUniform4uivDispatcher;

void glProgramUniformMatrix2dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix2dv = reinterpret_cast<glProgramUniformMatrix2dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix2dv"));
	glProgramUniformMatrix2dv(program,location,count,transpose,value);
}
glProgramUniformMatrix2dvCallback glProgramUniformMatrix2dv = glProgramUniformMatrix2dvDispatcher;

void glProgramUniformMatrix2fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix2fv = reinterpret_cast<glProgramUniformMatrix2fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix2fv"));
	glProgramUniformMatrix2fv(program,location,count,transpose,value);
}
glProgramUniformMatrix2fvCallback glProgramUniformMatrix2fv = glProgramUniformMatrix2fvDispatcher;

void glProgramUniformMatrix2x3dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix2x3dv = reinterpret_cast<glProgramUniformMatrix2x3dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix2x3dv"));
	glProgramUniformMatrix2x3dv(program,location,count,transpose,value);
}
glProgramUniformMatrix2x3dvCallback glProgramUniformMatrix2x3dv = glProgramUniformMatrix2x3dvDispatcher;

void glProgramUniformMatrix2x3fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix2x3fv = reinterpret_cast<glProgramUniformMatrix2x3fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix2x3fv"));
	glProgramUniformMatrix2x3fv(program,location,count,transpose,value);
}
glProgramUniformMatrix2x3fvCallback glProgramUniformMatrix2x3fv = glProgramUniformMatrix2x3fvDispatcher;

void glProgramUniformMatrix2x4dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix2x4dv = reinterpret_cast<glProgramUniformMatrix2x4dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix2x4dv"));
	glProgramUniformMatrix2x4dv(program,location,count,transpose,value);
}
glProgramUniformMatrix2x4dvCallback glProgramUniformMatrix2x4dv = glProgramUniformMatrix2x4dvDispatcher;

void glProgramUniformMatrix2x4fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix2x4fv = reinterpret_cast<glProgramUniformMatrix2x4fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix2x4fv"));
	glProgramUniformMatrix2x4fv(program,location,count,transpose,value);
}
glProgramUniformMatrix2x4fvCallback glProgramUniformMatrix2x4fv = glProgramUniformMatrix2x4fvDispatcher;

void glProgramUniformMatrix3dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix3dv = reinterpret_cast<glProgramUniformMatrix3dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix3dv"));
	glProgramUniformMatrix3dv(program,location,count,transpose,value);
}
glProgramUniformMatrix3dvCallback glProgramUniformMatrix3dv = glProgramUniformMatrix3dvDispatcher;

void glProgramUniformMatrix3fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix3fv = reinterpret_cast<glProgramUniformMatrix3fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix3fv"));
	glProgramUniformMatrix3fv(program,location,count,transpose,value);
}
glProgramUniformMatrix3fvCallback glProgramUniformMatrix3fv = glProgramUniformMatrix3fvDispatcher;

void glProgramUniformMatrix3x2dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix3x2dv = reinterpret_cast<glProgramUniformMatrix3x2dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix3x2dv"));
	glProgramUniformMatrix3x2dv(program,location,count,transpose,value);
}
glProgramUniformMatrix3x2dvCallback glProgramUniformMatrix3x2dv = glProgramUniformMatrix3x2dvDispatcher;

void glProgramUniformMatrix3x2fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix3x2fv = reinterpret_cast<glProgramUniformMatrix3x2fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix3x2fv"));
	glProgramUniformMatrix3x2fv(program,location,count,transpose,value);
}
glProgramUniformMatrix3x2fvCallback glProgramUniformMatrix3x2fv = glProgramUniformMatrix3x2fvDispatcher;

void glProgramUniformMatrix3x4dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix3x4dv = reinterpret_cast<glProgramUniformMatrix3x4dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix3x4dv"));
	glProgramUniformMatrix3x4dv(program,location,count,transpose,value);
}
glProgramUniformMatrix3x4dvCallback glProgramUniformMatrix3x4dv = glProgramUniformMatrix3x4dvDispatcher;

void glProgramUniformMatrix3x4fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix3x4fv = reinterpret_cast<glProgramUniformMatrix3x4fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix3x4fv"));
	glProgramUniformMatrix3x4fv(program,location,count,transpose,value);
}
glProgramUniformMatrix3x4fvCallback glProgramUniformMatrix3x4fv = glProgramUniformMatrix3x4fvDispatcher;

void glProgramUniformMatrix4dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix4dv = reinterpret_cast<glProgramUniformMatrix4dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix4dv"));
	glProgramUniformMatrix4dv(program,location,count,transpose,value);
}
glProgramUniformMatrix4dvCallback glProgramUniformMatrix4dv = glProgramUniformMatrix4dvDispatcher;

void glProgramUniformMatrix4fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix4fv = reinterpret_cast<glProgramUniformMatrix4fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix4fv"));
	glProgramUniformMatrix4fv(program,location,count,transpose,value);
}
glProgramUniformMatrix4fvCallback glProgramUniformMatrix4fv = glProgramUniformMatrix4fvDispatcher;

void glProgramUniformMatrix4x2dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix4x2dv = reinterpret_cast<glProgramUniformMatrix4x2dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix4x2dv"));
	glProgramUniformMatrix4x2dv(program,location,count,transpose,value);
}
glProgramUniformMatrix4x2dvCallback glProgramUniformMatrix4x2dv = glProgramUniformMatrix4x2dvDispatcher;

void glProgramUniformMatrix4x2fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix4x2fv = reinterpret_cast<glProgramUniformMatrix4x2fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix4x2fv"));
	glProgramUniformMatrix4x2fv(program,location,count,transpose,value);
}
glProgramUniformMatrix4x2fvCallback glProgramUniformMatrix4x2fv = glProgramUniformMatrix4x2fvDispatcher;

void glProgramUniformMatrix4x3dvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glProgramUniformMatrix4x3dv = reinterpret_cast<glProgramUniformMatrix4x3dvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix4x3dv"));
	glProgramUniformMatrix4x3dv(program,location,count,transpose,value);
}
glProgramUniformMatrix4x3dvCallback glProgramUniformMatrix4x3dv = glProgramUniformMatrix4x3dvDispatcher;

void glProgramUniformMatrix4x3fvDispatcher(GLuint program,GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glProgramUniformMatrix4x3fv = reinterpret_cast<glProgramUniformMatrix4x3fvCallback>(OpenGLGetProcAddress("glProgramUniformMatrix4x3fv"));
	glProgramUniformMatrix4x3fv(program,location,count,transpose,value);
}
glProgramUniformMatrix4x3fvCallback glProgramUniformMatrix4x3fv = glProgramUniformMatrix4x3fvDispatcher;

void glProvokingVertexDispatcher(GLenum mode){
	glProvokingVertex = reinterpret_cast<glProvokingVertexCallback>(OpenGLGetProcAddress("glProvokingVertex"));
	glProvokingVertex(mode);
}
glProvokingVertexCallback glProvokingVertex = glProvokingVertexDispatcher;

void glPushAttribDispatcher(GLbitfield mask){
	glPushAttrib = reinterpret_cast<glPushAttribCallback>(OpenGLGetProcAddress("glPushAttrib"));
	glPushAttrib(mask);
}
glPushAttribCallback glPushAttrib = glPushAttribDispatcher;

void glPushClientAttribDispatcher(GLbitfield mask){
	glPushClientAttrib = reinterpret_cast<glPushClientAttribCallback>(OpenGLGetProcAddress("glPushClientAttrib"));
	glPushClientAttrib(mask);
}
glPushClientAttribCallback glPushClientAttrib = glPushClientAttribDispatcher;

void glPushDebugGroupDispatcher(GLenum source,GLuint id,GLsizei length,const GLchar * message){
	glPushDebugGroup = reinterpret_cast<glPushDebugGroupCallback>(OpenGLGetProcAddress("glPushDebugGroup"));
	glPushDebugGroup(source,id,length,message);
}
glPushDebugGroupCallback glPushDebugGroup = glPushDebugGroupDispatcher;

void glPushMatrixDispatcher(){
	glPushMatrix = reinterpret_cast<glPushMatrixCallback>(OpenGLGetProcAddress("glPushMatrix"));
	glPushMatrix();
}
glPushMatrixCallback glPushMatrix = glPushMatrixDispatcher;

void glPushNameDispatcher(GLuint name){
	glPushName = reinterpret_cast<glPushNameCallback>(OpenGLGetProcAddress("glPushName"));
	glPushName(name);
}
glPushNameCallback glPushName = glPushNameDispatcher;

void glQueryCounterDispatcher(GLuint id,GLenum target){
	glQueryCounter = reinterpret_cast<glQueryCounterCallback>(OpenGLGetProcAddress("glQueryCounter"));
	glQueryCounter(id,target);
}
glQueryCounterCallback glQueryCounter = glQueryCounterDispatcher;

void glRasterPos2dDispatcher(GLdouble x,GLdouble y){
	glRasterPos2d = reinterpret_cast<glRasterPos2dCallback>(OpenGLGetProcAddress("glRasterPos2d"));
	glRasterPos2d(x,y);
}
glRasterPos2dCallback glRasterPos2d = glRasterPos2dDispatcher;

void glRasterPos2dvDispatcher(const GLdouble * v){
	glRasterPos2dv = reinterpret_cast<glRasterPos2dvCallback>(OpenGLGetProcAddress("glRasterPos2dv"));
	glRasterPos2dv(v);
}
glRasterPos2dvCallback glRasterPos2dv = glRasterPos2dvDispatcher;

void glRasterPos2fDispatcher(GLfloat x,GLfloat y){
	glRasterPos2f = reinterpret_cast<glRasterPos2fCallback>(OpenGLGetProcAddress("glRasterPos2f"));
	glRasterPos2f(x,y);
}
glRasterPos2fCallback glRasterPos2f = glRasterPos2fDispatcher;

void glRasterPos2fvDispatcher(const GLfloat * v){
	glRasterPos2fv = reinterpret_cast<glRasterPos2fvCallback>(OpenGLGetProcAddress("glRasterPos2fv"));
	glRasterPos2fv(v);
}
glRasterPos2fvCallback glRasterPos2fv = glRasterPos2fvDispatcher;

void glRasterPos2iDispatcher(GLint x,GLint y){
	glRasterPos2i = reinterpret_cast<glRasterPos2iCallback>(OpenGLGetProcAddress("glRasterPos2i"));
	glRasterPos2i(x,y);
}
glRasterPos2iCallback glRasterPos2i = glRasterPos2iDispatcher;

void glRasterPos2ivDispatcher(const GLint * v){
	glRasterPos2iv = reinterpret_cast<glRasterPos2ivCallback>(OpenGLGetProcAddress("glRasterPos2iv"));
	glRasterPos2iv(v);
}
glRasterPos2ivCallback glRasterPos2iv = glRasterPos2ivDispatcher;

void glRasterPos2sDispatcher(GLshort x,GLshort y){
	glRasterPos2s = reinterpret_cast<glRasterPos2sCallback>(OpenGLGetProcAddress("glRasterPos2s"));
	glRasterPos2s(x,y);
}
glRasterPos2sCallback glRasterPos2s = glRasterPos2sDispatcher;

void glRasterPos2svDispatcher(const GLshort * v){
	glRasterPos2sv = reinterpret_cast<glRasterPos2svCallback>(OpenGLGetProcAddress("glRasterPos2sv"));
	glRasterPos2sv(v);
}
glRasterPos2svCallback glRasterPos2sv = glRasterPos2svDispatcher;

void glRasterPos3dDispatcher(GLdouble x,GLdouble y,GLdouble z){
	glRasterPos3d = reinterpret_cast<glRasterPos3dCallback>(OpenGLGetProcAddress("glRasterPos3d"));
	glRasterPos3d(x,y,z);
}
glRasterPos3dCallback glRasterPos3d = glRasterPos3dDispatcher;

void glRasterPos3dvDispatcher(const GLdouble * v){
	glRasterPos3dv = reinterpret_cast<glRasterPos3dvCallback>(OpenGLGetProcAddress("glRasterPos3dv"));
	glRasterPos3dv(v);
}
glRasterPos3dvCallback glRasterPos3dv = glRasterPos3dvDispatcher;

void glRasterPos3fDispatcher(GLfloat x,GLfloat y,GLfloat z){
	glRasterPos3f = reinterpret_cast<glRasterPos3fCallback>(OpenGLGetProcAddress("glRasterPos3f"));
	glRasterPos3f(x,y,z);
}
glRasterPos3fCallback glRasterPos3f = glRasterPos3fDispatcher;

void glRasterPos3fvDispatcher(const GLfloat * v){
	glRasterPos3fv = reinterpret_cast<glRasterPos3fvCallback>(OpenGLGetProcAddress("glRasterPos3fv"));
	glRasterPos3fv(v);
}
glRasterPos3fvCallback glRasterPos3fv = glRasterPos3fvDispatcher;

void glRasterPos3iDispatcher(GLint x,GLint y,GLint z){
	glRasterPos3i = reinterpret_cast<glRasterPos3iCallback>(OpenGLGetProcAddress("glRasterPos3i"));
	glRasterPos3i(x,y,z);
}
glRasterPos3iCallback glRasterPos3i = glRasterPos3iDispatcher;

void glRasterPos3ivDispatcher(const GLint * v){
	glRasterPos3iv = reinterpret_cast<glRasterPos3ivCallback>(OpenGLGetProcAddress("glRasterPos3iv"));
	glRasterPos3iv(v);
}
glRasterPos3ivCallback glRasterPos3iv = glRasterPos3ivDispatcher;

void glRasterPos3sDispatcher(GLshort x,GLshort y,GLshort z){
	glRasterPos3s = reinterpret_cast<glRasterPos3sCallback>(OpenGLGetProcAddress("glRasterPos3s"));
	glRasterPos3s(x,y,z);
}
glRasterPos3sCallback glRasterPos3s = glRasterPos3sDispatcher;

void glRasterPos3svDispatcher(const GLshort * v){
	glRasterPos3sv = reinterpret_cast<glRasterPos3svCallback>(OpenGLGetProcAddress("glRasterPos3sv"));
	glRasterPos3sv(v);
}
glRasterPos3svCallback glRasterPos3sv = glRasterPos3svDispatcher;

void glRasterPos4dDispatcher(GLdouble x,GLdouble y,GLdouble z,GLdouble w){
	glRasterPos4d = reinterpret_cast<glRasterPos4dCallback>(OpenGLGetProcAddress("glRasterPos4d"));
	glRasterPos4d(x,y,z,w);
}
glRasterPos4dCallback glRasterPos4d = glRasterPos4dDispatcher;

void glRasterPos4dvDispatcher(const GLdouble * v){
	glRasterPos4dv = reinterpret_cast<glRasterPos4dvCallback>(OpenGLGetProcAddress("glRasterPos4dv"));
	glRasterPos4dv(v);
}
glRasterPos4dvCallback glRasterPos4dv = glRasterPos4dvDispatcher;

void glRasterPos4fDispatcher(GLfloat x,GLfloat y,GLfloat z,GLfloat w){
	glRasterPos4f = reinterpret_cast<glRasterPos4fCallback>(OpenGLGetProcAddress("glRasterPos4f"));
	glRasterPos4f(x,y,z,w);
}
glRasterPos4fCallback glRasterPos4f = glRasterPos4fDispatcher;

void glRasterPos4fvDispatcher(const GLfloat * v){
	glRasterPos4fv = reinterpret_cast<glRasterPos4fvCallback>(OpenGLGetProcAddress("glRasterPos4fv"));
	glRasterPos4fv(v);
}
glRasterPos4fvCallback glRasterPos4fv = glRasterPos4fvDispatcher;

void glRasterPos4iDispatcher(GLint x,GLint y,GLint z,GLint w){
	glRasterPos4i = reinterpret_cast<glRasterPos4iCallback>(OpenGLGetProcAddress("glRasterPos4i"));
	glRasterPos4i(x,y,z,w);
}
glRasterPos4iCallback glRasterPos4i = glRasterPos4iDispatcher;

void glRasterPos4ivDispatcher(const GLint * v){
	glRasterPos4iv = reinterpret_cast<glRasterPos4ivCallback>(OpenGLGetProcAddress("glRasterPos4iv"));
	glRasterPos4iv(v);
}
glRasterPos4ivCallback glRasterPos4iv = glRasterPos4ivDispatcher;

void glRasterPos4sDispatcher(GLshort x,GLshort y,GLshort z,GLshort w){
	glRasterPos4s = reinterpret_cast<glRasterPos4sCallback>(OpenGLGetProcAddress("glRasterPos4s"));
	glRasterPos4s(x,y,z,w);
}
glRasterPos4sCallback glRasterPos4s = glRasterPos4sDispatcher;

void glRasterPos4svDispatcher(const GLshort * v){
	glRasterPos4sv = reinterpret_cast<glRasterPos4svCallback>(OpenGLGetProcAddress("glRasterPos4sv"));
	glRasterPos4sv(v);
}
glRasterPos4svCallback glRasterPos4sv = glRasterPos4svDispatcher;

void glReadBufferDispatcher(GLenum src){
	glReadBuffer = reinterpret_cast<glReadBufferCallback>(OpenGLGetProcAddress("glReadBuffer"));
	glReadBuffer(src);
}
glReadBufferCallback glReadBuffer = glReadBufferDispatcher;

void glReadPixelsDispatcher(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,void * pixels){
	glReadPixels = reinterpret_cast<glReadPixelsCallback>(OpenGLGetProcAddress("glReadPixels"));
	glReadPixels(x,y,width,height,format,type,pixels);
}
glReadPixelsCallback glReadPixels = glReadPixelsDispatcher;

void glReadnPixelsDispatcher(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLsizei bufSize,void * data){
	glReadnPixels = reinterpret_cast<glReadnPixelsCallback>(OpenGLGetProcAddress("glReadnPixels"));
	glReadnPixels(x,y,width,height,format,type,bufSize,data);
}
glReadnPixelsCallback glReadnPixels = glReadnPixelsDispatcher;

void glRectdDispatcher(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2){
	glRectd = reinterpret_cast<glRectdCallback>(OpenGLGetProcAddress("glRectd"));
	glRectd(x1,y1,x2,y2);
}
glRectdCallback glRectd = glRectdDispatcher;

void glRectdvDispatcher(const GLdouble * v1,const GLdouble * v2){
	glRectdv = reinterpret_cast<glRectdvCallback>(OpenGLGetProcAddress("glRectdv"));
	glRectdv(v1,v2);
}
glRectdvCallback glRectdv = glRectdvDispatcher;

void glRectfDispatcher(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2){
	glRectf = reinterpret_cast<glRectfCallback>(OpenGLGetProcAddress("glRectf"));
	glRectf(x1,y1,x2,y2);
}
glRectfCallback glRectf = glRectfDispatcher;

void glRectfvDispatcher(const GLfloat * v1,const GLfloat * v2){
	glRectfv = reinterpret_cast<glRectfvCallback>(OpenGLGetProcAddress("glRectfv"));
	glRectfv(v1,v2);
}
glRectfvCallback glRectfv = glRectfvDispatcher;

void glRectiDispatcher(GLint x1,GLint y1,GLint x2,GLint y2){
	glRecti = reinterpret_cast<glRectiCallback>(OpenGLGetProcAddress("glRecti"));
	glRecti(x1,y1,x2,y2);
}
glRectiCallback glRecti = glRectiDispatcher;

void glRectivDispatcher(const GLint * v1,const GLint * v2){
	glRectiv = reinterpret_cast<glRectivCallback>(OpenGLGetProcAddress("glRectiv"));
	glRectiv(v1,v2);
}
glRectivCallback glRectiv = glRectivDispatcher;

void glRectsDispatcher(GLshort x1,GLshort y1,GLshort x2,GLshort y2){
	glRects = reinterpret_cast<glRectsCallback>(OpenGLGetProcAddress("glRects"));
	glRects(x1,y1,x2,y2);
}
glRectsCallback glRects = glRectsDispatcher;

void glRectsvDispatcher(const GLshort * v1,const GLshort * v2){
	glRectsv = reinterpret_cast<glRectsvCallback>(OpenGLGetProcAddress("glRectsv"));
	glRectsv(v1,v2);
}
glRectsvCallback glRectsv = glRectsvDispatcher;

void glReleaseShaderCompilerDispatcher(){
	glReleaseShaderCompiler = reinterpret_cast<glReleaseShaderCompilerCallback>(OpenGLGetProcAddress("glReleaseShaderCompiler"));
	glReleaseShaderCompiler();
}
glReleaseShaderCompilerCallback glReleaseShaderCompiler = glReleaseShaderCompilerDispatcher;

GLint glRenderModeDispatcher(GLenum mode){
	glRenderMode = reinterpret_cast<glRenderModeCallback>(OpenGLGetProcAddress("glRenderMode"));
	return 	glRenderMode(mode);
}
glRenderModeCallback glRenderMode = glRenderModeDispatcher;

void glRenderbufferStorageDispatcher(GLenum target,GLenum internalformat,GLsizei width,GLsizei height){
	glRenderbufferStorage = reinterpret_cast<glRenderbufferStorageCallback>(OpenGLGetProcAddress("glRenderbufferStorage"));
	glRenderbufferStorage(target,internalformat,width,height);
}
glRenderbufferStorageCallback glRenderbufferStorage = glRenderbufferStorageDispatcher;

void glRenderbufferStorageMultisampleDispatcher(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height){
	glRenderbufferStorageMultisample = reinterpret_cast<glRenderbufferStorageMultisampleCallback>(OpenGLGetProcAddress("glRenderbufferStorageMultisample"));
	glRenderbufferStorageMultisample(target,samples,internalformat,width,height);
}
glRenderbufferStorageMultisampleCallback glRenderbufferStorageMultisample = glRenderbufferStorageMultisampleDispatcher;

void glResumeTransformFeedbackDispatcher(){
	glResumeTransformFeedback = reinterpret_cast<glResumeTransformFeedbackCallback>(OpenGLGetProcAddress("glResumeTransformFeedback"));
	glResumeTransformFeedback();
}
glResumeTransformFeedbackCallback glResumeTransformFeedback = glResumeTransformFeedbackDispatcher;

void glRotatedDispatcher(GLdouble angle,GLdouble x,GLdouble y,GLdouble z){
	glRotated = reinterpret_cast<glRotatedCallback>(OpenGLGetProcAddress("glRotated"));
	glRotated(angle,x,y,z);
}
glRotatedCallback glRotated = glRotatedDispatcher;

void glRotatefDispatcher(GLfloat angle,GLfloat x,GLfloat y,GLfloat z){
	glRotatef = reinterpret_cast<glRotatefCallback>(OpenGLGetProcAddress("glRotatef"));
	glRotatef(angle,x,y,z);
}
glRotatefCallback glRotatef = glRotatefDispatcher;

void glSampleCoverageDispatcher(GLfloat value,GLboolean invert){
	glSampleCoverage = reinterpret_cast<glSampleCoverageCallback>(OpenGLGetProcAddress("glSampleCoverage"));
	glSampleCoverage(value,invert);
}
glSampleCoverageCallback glSampleCoverage = glSampleCoverageDispatcher;

void glSampleMaskiDispatcher(GLuint maskNumber,GLbitfield mask){
	glSampleMaski = reinterpret_cast<glSampleMaskiCallback>(OpenGLGetProcAddress("glSampleMaski"));
	glSampleMaski(maskNumber,mask);
}
glSampleMaskiCallback glSampleMaski = glSampleMaskiDispatcher;

void glSamplerParameterIivDispatcher(GLuint sampler,GLenum pname,const GLint * param){
	glSamplerParameterIiv = reinterpret_cast<glSamplerParameterIivCallback>(OpenGLGetProcAddress("glSamplerParameterIiv"));
	glSamplerParameterIiv(sampler,pname,param);
}
glSamplerParameterIivCallback glSamplerParameterIiv = glSamplerParameterIivDispatcher;

void glSamplerParameterIuivDispatcher(GLuint sampler,GLenum pname,const GLuint * param){
	glSamplerParameterIuiv = reinterpret_cast<glSamplerParameterIuivCallback>(OpenGLGetProcAddress("glSamplerParameterIuiv"));
	glSamplerParameterIuiv(sampler,pname,param);
}
glSamplerParameterIuivCallback glSamplerParameterIuiv = glSamplerParameterIuivDispatcher;

void glSamplerParameterfDispatcher(GLuint sampler,GLenum pname,GLfloat param){
	glSamplerParameterf = reinterpret_cast<glSamplerParameterfCallback>(OpenGLGetProcAddress("glSamplerParameterf"));
	glSamplerParameterf(sampler,pname,param);
}
glSamplerParameterfCallback glSamplerParameterf = glSamplerParameterfDispatcher;

void glSamplerParameterfvDispatcher(GLuint sampler,GLenum pname,const GLfloat * param){
	glSamplerParameterfv = reinterpret_cast<glSamplerParameterfvCallback>(OpenGLGetProcAddress("glSamplerParameterfv"));
	glSamplerParameterfv(sampler,pname,param);
}
glSamplerParameterfvCallback glSamplerParameterfv = glSamplerParameterfvDispatcher;

void glSamplerParameteriDispatcher(GLuint sampler,GLenum pname,GLint param){
	glSamplerParameteri = reinterpret_cast<glSamplerParameteriCallback>(OpenGLGetProcAddress("glSamplerParameteri"));
	glSamplerParameteri(sampler,pname,param);
}
glSamplerParameteriCallback glSamplerParameteri = glSamplerParameteriDispatcher;

void glSamplerParameterivDispatcher(GLuint sampler,GLenum pname,const GLint * param){
	glSamplerParameteriv = reinterpret_cast<glSamplerParameterivCallback>(OpenGLGetProcAddress("glSamplerParameteriv"));
	glSamplerParameteriv(sampler,pname,param);
}
glSamplerParameterivCallback glSamplerParameteriv = glSamplerParameterivDispatcher;

void glScaledDispatcher(GLdouble x,GLdouble y,GLdouble z){
	glScaled = reinterpret_cast<glScaledCallback>(OpenGLGetProcAddress("glScaled"));
	glScaled(x,y,z);
}
glScaledCallback glScaled = glScaledDispatcher;

void glScalefDispatcher(GLfloat x,GLfloat y,GLfloat z){
	glScalef = reinterpret_cast<glScalefCallback>(OpenGLGetProcAddress("glScalef"));
	glScalef(x,y,z);
}
glScalefCallback glScalef = glScalefDispatcher;

void glScissorDispatcher(GLint x,GLint y,GLsizei width,GLsizei height){
	glScissor = reinterpret_cast<glScissorCallback>(OpenGLGetProcAddress("glScissor"));
	glScissor(x,y,width,height);
}
glScissorCallback glScissor = glScissorDispatcher;

void glScissorArrayvDispatcher(GLuint first,GLsizei count,const GLint * v){
	glScissorArrayv = reinterpret_cast<glScissorArrayvCallback>(OpenGLGetProcAddress("glScissorArrayv"));
	glScissorArrayv(first,count,v);
}
glScissorArrayvCallback glScissorArrayv = glScissorArrayvDispatcher;

void glScissorIndexedDispatcher(GLuint index,GLint left,GLint bottom,GLsizei width,GLsizei height){
	glScissorIndexed = reinterpret_cast<glScissorIndexedCallback>(OpenGLGetProcAddress("glScissorIndexed"));
	glScissorIndexed(index,left,bottom,width,height);
}
glScissorIndexedCallback glScissorIndexed = glScissorIndexedDispatcher;

void glScissorIndexedvDispatcher(GLuint index,const GLint * v){
	glScissorIndexedv = reinterpret_cast<glScissorIndexedvCallback>(OpenGLGetProcAddress("glScissorIndexedv"));
	glScissorIndexedv(index,v);
}
glScissorIndexedvCallback glScissorIndexedv = glScissorIndexedvDispatcher;

void glSecondaryColor3bDispatcher(GLbyte red,GLbyte green,GLbyte blue){
	glSecondaryColor3b = reinterpret_cast<glSecondaryColor3bCallback>(OpenGLGetProcAddress("glSecondaryColor3b"));
	glSecondaryColor3b(red,green,blue);
}
glSecondaryColor3bCallback glSecondaryColor3b = glSecondaryColor3bDispatcher;

void glSecondaryColor3bvDispatcher(const GLbyte * v){
	glSecondaryColor3bv = reinterpret_cast<glSecondaryColor3bvCallback>(OpenGLGetProcAddress("glSecondaryColor3bv"));
	glSecondaryColor3bv(v);
}
glSecondaryColor3bvCallback glSecondaryColor3bv = glSecondaryColor3bvDispatcher;

void glSecondaryColor3dDispatcher(GLdouble red,GLdouble green,GLdouble blue){
	glSecondaryColor3d = reinterpret_cast<glSecondaryColor3dCallback>(OpenGLGetProcAddress("glSecondaryColor3d"));
	glSecondaryColor3d(red,green,blue);
}
glSecondaryColor3dCallback glSecondaryColor3d = glSecondaryColor3dDispatcher;

void glSecondaryColor3dvDispatcher(const GLdouble * v){
	glSecondaryColor3dv = reinterpret_cast<glSecondaryColor3dvCallback>(OpenGLGetProcAddress("glSecondaryColor3dv"));
	glSecondaryColor3dv(v);
}
glSecondaryColor3dvCallback glSecondaryColor3dv = glSecondaryColor3dvDispatcher;

void glSecondaryColor3fDispatcher(GLfloat red,GLfloat green,GLfloat blue){
	glSecondaryColor3f = reinterpret_cast<glSecondaryColor3fCallback>(OpenGLGetProcAddress("glSecondaryColor3f"));
	glSecondaryColor3f(red,green,blue);
}
glSecondaryColor3fCallback glSecondaryColor3f = glSecondaryColor3fDispatcher;

void glSecondaryColor3fvDispatcher(const GLfloat * v){
	glSecondaryColor3fv = reinterpret_cast<glSecondaryColor3fvCallback>(OpenGLGetProcAddress("glSecondaryColor3fv"));
	glSecondaryColor3fv(v);
}
glSecondaryColor3fvCallback glSecondaryColor3fv = glSecondaryColor3fvDispatcher;

void glSecondaryColor3iDispatcher(GLint red,GLint green,GLint blue){
	glSecondaryColor3i = reinterpret_cast<glSecondaryColor3iCallback>(OpenGLGetProcAddress("glSecondaryColor3i"));
	glSecondaryColor3i(red,green,blue);
}
glSecondaryColor3iCallback glSecondaryColor3i = glSecondaryColor3iDispatcher;

void glSecondaryColor3ivDispatcher(const GLint * v){
	glSecondaryColor3iv = reinterpret_cast<glSecondaryColor3ivCallback>(OpenGLGetProcAddress("glSecondaryColor3iv"));
	glSecondaryColor3iv(v);
}
glSecondaryColor3ivCallback glSecondaryColor3iv = glSecondaryColor3ivDispatcher;

void glSecondaryColor3sDispatcher(GLshort red,GLshort green,GLshort blue){
	glSecondaryColor3s = reinterpret_cast<glSecondaryColor3sCallback>(OpenGLGetProcAddress("glSecondaryColor3s"));
	glSecondaryColor3s(red,green,blue);
}
glSecondaryColor3sCallback glSecondaryColor3s = glSecondaryColor3sDispatcher;

void glSecondaryColor3svDispatcher(const GLshort * v){
	glSecondaryColor3sv = reinterpret_cast<glSecondaryColor3svCallback>(OpenGLGetProcAddress("glSecondaryColor3sv"));
	glSecondaryColor3sv(v);
}
glSecondaryColor3svCallback glSecondaryColor3sv = glSecondaryColor3svDispatcher;

void glSecondaryColor3ubDispatcher(GLubyte red,GLubyte green,GLubyte blue){
	glSecondaryColor3ub = reinterpret_cast<glSecondaryColor3ubCallback>(OpenGLGetProcAddress("glSecondaryColor3ub"));
	glSecondaryColor3ub(red,green,blue);
}
glSecondaryColor3ubCallback glSecondaryColor3ub = glSecondaryColor3ubDispatcher;

void glSecondaryColor3ubvDispatcher(const GLubyte * v){
	glSecondaryColor3ubv = reinterpret_cast<glSecondaryColor3ubvCallback>(OpenGLGetProcAddress("glSecondaryColor3ubv"));
	glSecondaryColor3ubv(v);
}
glSecondaryColor3ubvCallback glSecondaryColor3ubv = glSecondaryColor3ubvDispatcher;

void glSecondaryColor3uiDispatcher(GLuint red,GLuint green,GLuint blue){
	glSecondaryColor3ui = reinterpret_cast<glSecondaryColor3uiCallback>(OpenGLGetProcAddress("glSecondaryColor3ui"));
	glSecondaryColor3ui(red,green,blue);
}
glSecondaryColor3uiCallback glSecondaryColor3ui = glSecondaryColor3uiDispatcher;

void glSecondaryColor3uivDispatcher(const GLuint * v){
	glSecondaryColor3uiv = reinterpret_cast<glSecondaryColor3uivCallback>(OpenGLGetProcAddress("glSecondaryColor3uiv"));
	glSecondaryColor3uiv(v);
}
glSecondaryColor3uivCallback glSecondaryColor3uiv = glSecondaryColor3uivDispatcher;

void glSecondaryColor3usDispatcher(GLushort red,GLushort green,GLushort blue){
	glSecondaryColor3us = reinterpret_cast<glSecondaryColor3usCallback>(OpenGLGetProcAddress("glSecondaryColor3us"));
	glSecondaryColor3us(red,green,blue);
}
glSecondaryColor3usCallback glSecondaryColor3us = glSecondaryColor3usDispatcher;

void glSecondaryColor3usvDispatcher(const GLushort * v){
	glSecondaryColor3usv = reinterpret_cast<glSecondaryColor3usvCallback>(OpenGLGetProcAddress("glSecondaryColor3usv"));
	glSecondaryColor3usv(v);
}
glSecondaryColor3usvCallback glSecondaryColor3usv = glSecondaryColor3usvDispatcher;

void glSecondaryColorP3uiDispatcher(GLenum type,GLuint color){
	glSecondaryColorP3ui = reinterpret_cast<glSecondaryColorP3uiCallback>(OpenGLGetProcAddress("glSecondaryColorP3ui"));
	glSecondaryColorP3ui(type,color);
}
glSecondaryColorP3uiCallback glSecondaryColorP3ui = glSecondaryColorP3uiDispatcher;

void glSecondaryColorP3uivDispatcher(GLenum type,const GLuint * color){
	glSecondaryColorP3uiv = reinterpret_cast<glSecondaryColorP3uivCallback>(OpenGLGetProcAddress("glSecondaryColorP3uiv"));
	glSecondaryColorP3uiv(type,color);
}
glSecondaryColorP3uivCallback glSecondaryColorP3uiv = glSecondaryColorP3uivDispatcher;

void glSecondaryColorPointerDispatcher(GLint size,GLenum type,GLsizei stride,const void * pointer){
	glSecondaryColorPointer = reinterpret_cast<glSecondaryColorPointerCallback>(OpenGLGetProcAddress("glSecondaryColorPointer"));
	glSecondaryColorPointer(size,type,stride,pointer);
}
glSecondaryColorPointerCallback glSecondaryColorPointer = glSecondaryColorPointerDispatcher;

void glSelectBufferDispatcher(GLsizei size,GLuint * buffer){
	glSelectBuffer = reinterpret_cast<glSelectBufferCallback>(OpenGLGetProcAddress("glSelectBuffer"));
	glSelectBuffer(size,buffer);
}
glSelectBufferCallback glSelectBuffer = glSelectBufferDispatcher;

void glShadeModelDispatcher(GLenum mode){
	glShadeModel = reinterpret_cast<glShadeModelCallback>(OpenGLGetProcAddress("glShadeModel"));
	glShadeModel(mode);
}
glShadeModelCallback glShadeModel = glShadeModelDispatcher;

void glShaderBinaryDispatcher(GLsizei count,const GLuint * shaders,GLenum binaryformat,const void * binary,GLsizei length){
	glShaderBinary = reinterpret_cast<glShaderBinaryCallback>(OpenGLGetProcAddress("glShaderBinary"));
	glShaderBinary(count,shaders,binaryformat,binary,length);
}
glShaderBinaryCallback glShaderBinary = glShaderBinaryDispatcher;

void glShaderSourceDispatcher(GLuint shader,GLsizei count,const GLchar *const* string,const GLint * length){
	glShaderSource = reinterpret_cast<glShaderSourceCallback>(OpenGLGetProcAddress("glShaderSource"));
	glShaderSource(shader,count,string,length);
}
glShaderSourceCallback glShaderSource = glShaderSourceDispatcher;

void glShaderStorageBlockBindingDispatcher(GLuint program,GLuint storageBlockIndex,GLuint storageBlockBinding){
	glShaderStorageBlockBinding = reinterpret_cast<glShaderStorageBlockBindingCallback>(OpenGLGetProcAddress("glShaderStorageBlockBinding"));
	glShaderStorageBlockBinding(program,storageBlockIndex,storageBlockBinding);
}
glShaderStorageBlockBindingCallback glShaderStorageBlockBinding = glShaderStorageBlockBindingDispatcher;

void glStencilFuncDispatcher(GLenum func,GLint ref,GLuint mask){
	glStencilFunc = reinterpret_cast<glStencilFuncCallback>(OpenGLGetProcAddress("glStencilFunc"));
	glStencilFunc(func,ref,mask);
}
glStencilFuncCallback glStencilFunc = glStencilFuncDispatcher;

void glStencilFuncSeparateDispatcher(GLenum face,GLenum func,GLint ref,GLuint mask){
	glStencilFuncSeparate = reinterpret_cast<glStencilFuncSeparateCallback>(OpenGLGetProcAddress("glStencilFuncSeparate"));
	glStencilFuncSeparate(face,func,ref,mask);
}
glStencilFuncSeparateCallback glStencilFuncSeparate = glStencilFuncSeparateDispatcher;

void glStencilMaskDispatcher(GLuint mask){
	glStencilMask = reinterpret_cast<glStencilMaskCallback>(OpenGLGetProcAddress("glStencilMask"));
	glStencilMask(mask);
}
glStencilMaskCallback glStencilMask = glStencilMaskDispatcher;

void glStencilMaskSeparateDispatcher(GLenum face,GLuint mask){
	glStencilMaskSeparate = reinterpret_cast<glStencilMaskSeparateCallback>(OpenGLGetProcAddress("glStencilMaskSeparate"));
	glStencilMaskSeparate(face,mask);
}
glStencilMaskSeparateCallback glStencilMaskSeparate = glStencilMaskSeparateDispatcher;

void glStencilOpDispatcher(GLenum fail,GLenum zfail,GLenum zpass){
	glStencilOp = reinterpret_cast<glStencilOpCallback>(OpenGLGetProcAddress("glStencilOp"));
	glStencilOp(fail,zfail,zpass);
}
glStencilOpCallback glStencilOp = glStencilOpDispatcher;

void glStencilOpSeparateDispatcher(GLenum face,GLenum sfail,GLenum dpfail,GLenum dppass){
	glStencilOpSeparate = reinterpret_cast<glStencilOpSeparateCallback>(OpenGLGetProcAddress("glStencilOpSeparate"));
	glStencilOpSeparate(face,sfail,dpfail,dppass);
}
glStencilOpSeparateCallback glStencilOpSeparate = glStencilOpSeparateDispatcher;

void glTexBufferDispatcher(GLenum target,GLenum internalformat,GLuint buffer){
	glTexBuffer = reinterpret_cast<glTexBufferCallback>(OpenGLGetProcAddress("glTexBuffer"));
	glTexBuffer(target,internalformat,buffer);
}
glTexBufferCallback glTexBuffer = glTexBufferDispatcher;

void glTexBufferRangeDispatcher(GLenum target,GLenum internalformat,GLuint buffer,GLintptr offset,GLsizeiptr size){
	glTexBufferRange = reinterpret_cast<glTexBufferRangeCallback>(OpenGLGetProcAddress("glTexBufferRange"));
	glTexBufferRange(target,internalformat,buffer,offset,size);
}
glTexBufferRangeCallback glTexBufferRange = glTexBufferRangeDispatcher;

void glTexCoord1dDispatcher(GLdouble s){
	glTexCoord1d = reinterpret_cast<glTexCoord1dCallback>(OpenGLGetProcAddress("glTexCoord1d"));
	glTexCoord1d(s);
}
glTexCoord1dCallback glTexCoord1d = glTexCoord1dDispatcher;

void glTexCoord1dvDispatcher(const GLdouble * v){
	glTexCoord1dv = reinterpret_cast<glTexCoord1dvCallback>(OpenGLGetProcAddress("glTexCoord1dv"));
	glTexCoord1dv(v);
}
glTexCoord1dvCallback glTexCoord1dv = glTexCoord1dvDispatcher;

void glTexCoord1fDispatcher(GLfloat s){
	glTexCoord1f = reinterpret_cast<glTexCoord1fCallback>(OpenGLGetProcAddress("glTexCoord1f"));
	glTexCoord1f(s);
}
glTexCoord1fCallback glTexCoord1f = glTexCoord1fDispatcher;

void glTexCoord1fvDispatcher(const GLfloat * v){
	glTexCoord1fv = reinterpret_cast<glTexCoord1fvCallback>(OpenGLGetProcAddress("glTexCoord1fv"));
	glTexCoord1fv(v);
}
glTexCoord1fvCallback glTexCoord1fv = glTexCoord1fvDispatcher;

void glTexCoord1iDispatcher(GLint s){
	glTexCoord1i = reinterpret_cast<glTexCoord1iCallback>(OpenGLGetProcAddress("glTexCoord1i"));
	glTexCoord1i(s);
}
glTexCoord1iCallback glTexCoord1i = glTexCoord1iDispatcher;

void glTexCoord1ivDispatcher(const GLint * v){
	glTexCoord1iv = reinterpret_cast<glTexCoord1ivCallback>(OpenGLGetProcAddress("glTexCoord1iv"));
	glTexCoord1iv(v);
}
glTexCoord1ivCallback glTexCoord1iv = glTexCoord1ivDispatcher;

void glTexCoord1sDispatcher(GLshort s){
	glTexCoord1s = reinterpret_cast<glTexCoord1sCallback>(OpenGLGetProcAddress("glTexCoord1s"));
	glTexCoord1s(s);
}
glTexCoord1sCallback glTexCoord1s = glTexCoord1sDispatcher;

void glTexCoord1svDispatcher(const GLshort * v){
	glTexCoord1sv = reinterpret_cast<glTexCoord1svCallback>(OpenGLGetProcAddress("glTexCoord1sv"));
	glTexCoord1sv(v);
}
glTexCoord1svCallback glTexCoord1sv = glTexCoord1svDispatcher;

void glTexCoord2dDispatcher(GLdouble s,GLdouble t){
	glTexCoord2d = reinterpret_cast<glTexCoord2dCallback>(OpenGLGetProcAddress("glTexCoord2d"));
	glTexCoord2d(s,t);
}
glTexCoord2dCallback glTexCoord2d = glTexCoord2dDispatcher;

void glTexCoord2dvDispatcher(const GLdouble * v){
	glTexCoord2dv = reinterpret_cast<glTexCoord2dvCallback>(OpenGLGetProcAddress("glTexCoord2dv"));
	glTexCoord2dv(v);
}
glTexCoord2dvCallback glTexCoord2dv = glTexCoord2dvDispatcher;

void glTexCoord2fDispatcher(GLfloat s,GLfloat t){
	glTexCoord2f = reinterpret_cast<glTexCoord2fCallback>(OpenGLGetProcAddress("glTexCoord2f"));
	glTexCoord2f(s,t);
}
glTexCoord2fCallback glTexCoord2f = glTexCoord2fDispatcher;

void glTexCoord2fvDispatcher(const GLfloat * v){
	glTexCoord2fv = reinterpret_cast<glTexCoord2fvCallback>(OpenGLGetProcAddress("glTexCoord2fv"));
	glTexCoord2fv(v);
}
glTexCoord2fvCallback glTexCoord2fv = glTexCoord2fvDispatcher;

void glTexCoord2iDispatcher(GLint s,GLint t){
	glTexCoord2i = reinterpret_cast<glTexCoord2iCallback>(OpenGLGetProcAddress("glTexCoord2i"));
	glTexCoord2i(s,t);
}
glTexCoord2iCallback glTexCoord2i = glTexCoord2iDispatcher;

void glTexCoord2ivDispatcher(const GLint * v){
	glTexCoord2iv = reinterpret_cast<glTexCoord2ivCallback>(OpenGLGetProcAddress("glTexCoord2iv"));
	glTexCoord2iv(v);
}
glTexCoord2ivCallback glTexCoord2iv = glTexCoord2ivDispatcher;

void glTexCoord2sDispatcher(GLshort s,GLshort t){
	glTexCoord2s = reinterpret_cast<glTexCoord2sCallback>(OpenGLGetProcAddress("glTexCoord2s"));
	glTexCoord2s(s,t);
}
glTexCoord2sCallback glTexCoord2s = glTexCoord2sDispatcher;

void glTexCoord2svDispatcher(const GLshort * v){
	glTexCoord2sv = reinterpret_cast<glTexCoord2svCallback>(OpenGLGetProcAddress("glTexCoord2sv"));
	glTexCoord2sv(v);
}
glTexCoord2svCallback glTexCoord2sv = glTexCoord2svDispatcher;

void glTexCoord3dDispatcher(GLdouble s,GLdouble t,GLdouble r){
	glTexCoord3d = reinterpret_cast<glTexCoord3dCallback>(OpenGLGetProcAddress("glTexCoord3d"));
	glTexCoord3d(s,t,r);
}
glTexCoord3dCallback glTexCoord3d = glTexCoord3dDispatcher;

void glTexCoord3dvDispatcher(const GLdouble * v){
	glTexCoord3dv = reinterpret_cast<glTexCoord3dvCallback>(OpenGLGetProcAddress("glTexCoord3dv"));
	glTexCoord3dv(v);
}
glTexCoord3dvCallback glTexCoord3dv = glTexCoord3dvDispatcher;

void glTexCoord3fDispatcher(GLfloat s,GLfloat t,GLfloat r){
	glTexCoord3f = reinterpret_cast<glTexCoord3fCallback>(OpenGLGetProcAddress("glTexCoord3f"));
	glTexCoord3f(s,t,r);
}
glTexCoord3fCallback glTexCoord3f = glTexCoord3fDispatcher;

void glTexCoord3fvDispatcher(const GLfloat * v){
	glTexCoord3fv = reinterpret_cast<glTexCoord3fvCallback>(OpenGLGetProcAddress("glTexCoord3fv"));
	glTexCoord3fv(v);
}
glTexCoord3fvCallback glTexCoord3fv = glTexCoord3fvDispatcher;

void glTexCoord3iDispatcher(GLint s,GLint t,GLint r){
	glTexCoord3i = reinterpret_cast<glTexCoord3iCallback>(OpenGLGetProcAddress("glTexCoord3i"));
	glTexCoord3i(s,t,r);
}
glTexCoord3iCallback glTexCoord3i = glTexCoord3iDispatcher;

void glTexCoord3ivDispatcher(const GLint * v){
	glTexCoord3iv = reinterpret_cast<glTexCoord3ivCallback>(OpenGLGetProcAddress("glTexCoord3iv"));
	glTexCoord3iv(v);
}
glTexCoord3ivCallback glTexCoord3iv = glTexCoord3ivDispatcher;

void glTexCoord3sDispatcher(GLshort s,GLshort t,GLshort r){
	glTexCoord3s = reinterpret_cast<glTexCoord3sCallback>(OpenGLGetProcAddress("glTexCoord3s"));
	glTexCoord3s(s,t,r);
}
glTexCoord3sCallback glTexCoord3s = glTexCoord3sDispatcher;

void glTexCoord3svDispatcher(const GLshort * v){
	glTexCoord3sv = reinterpret_cast<glTexCoord3svCallback>(OpenGLGetProcAddress("glTexCoord3sv"));
	glTexCoord3sv(v);
}
glTexCoord3svCallback glTexCoord3sv = glTexCoord3svDispatcher;

void glTexCoord4dDispatcher(GLdouble s,GLdouble t,GLdouble r,GLdouble q){
	glTexCoord4d = reinterpret_cast<glTexCoord4dCallback>(OpenGLGetProcAddress("glTexCoord4d"));
	glTexCoord4d(s,t,r,q);
}
glTexCoord4dCallback glTexCoord4d = glTexCoord4dDispatcher;

void glTexCoord4dvDispatcher(const GLdouble * v){
	glTexCoord4dv = reinterpret_cast<glTexCoord4dvCallback>(OpenGLGetProcAddress("glTexCoord4dv"));
	glTexCoord4dv(v);
}
glTexCoord4dvCallback glTexCoord4dv = glTexCoord4dvDispatcher;

void glTexCoord4fDispatcher(GLfloat s,GLfloat t,GLfloat r,GLfloat q){
	glTexCoord4f = reinterpret_cast<glTexCoord4fCallback>(OpenGLGetProcAddress("glTexCoord4f"));
	glTexCoord4f(s,t,r,q);
}
glTexCoord4fCallback glTexCoord4f = glTexCoord4fDispatcher;

void glTexCoord4fvDispatcher(const GLfloat * v){
	glTexCoord4fv = reinterpret_cast<glTexCoord4fvCallback>(OpenGLGetProcAddress("glTexCoord4fv"));
	glTexCoord4fv(v);
}
glTexCoord4fvCallback glTexCoord4fv = glTexCoord4fvDispatcher;

void glTexCoord4iDispatcher(GLint s,GLint t,GLint r,GLint q){
	glTexCoord4i = reinterpret_cast<glTexCoord4iCallback>(OpenGLGetProcAddress("glTexCoord4i"));
	glTexCoord4i(s,t,r,q);
}
glTexCoord4iCallback glTexCoord4i = glTexCoord4iDispatcher;

void glTexCoord4ivDispatcher(const GLint * v){
	glTexCoord4iv = reinterpret_cast<glTexCoord4ivCallback>(OpenGLGetProcAddress("glTexCoord4iv"));
	glTexCoord4iv(v);
}
glTexCoord4ivCallback glTexCoord4iv = glTexCoord4ivDispatcher;

void glTexCoord4sDispatcher(GLshort s,GLshort t,GLshort r,GLshort q){
	glTexCoord4s = reinterpret_cast<glTexCoord4sCallback>(OpenGLGetProcAddress("glTexCoord4s"));
	glTexCoord4s(s,t,r,q);
}
glTexCoord4sCallback glTexCoord4s = glTexCoord4sDispatcher;

void glTexCoord4svDispatcher(const GLshort * v){
	glTexCoord4sv = reinterpret_cast<glTexCoord4svCallback>(OpenGLGetProcAddress("glTexCoord4sv"));
	glTexCoord4sv(v);
}
glTexCoord4svCallback glTexCoord4sv = glTexCoord4svDispatcher;

void glTexCoordP1uiDispatcher(GLenum type,GLuint coords){
	glTexCoordP1ui = reinterpret_cast<glTexCoordP1uiCallback>(OpenGLGetProcAddress("glTexCoordP1ui"));
	glTexCoordP1ui(type,coords);
}
glTexCoordP1uiCallback glTexCoordP1ui = glTexCoordP1uiDispatcher;

void glTexCoordP1uivDispatcher(GLenum type,const GLuint * coords){
	glTexCoordP1uiv = reinterpret_cast<glTexCoordP1uivCallback>(OpenGLGetProcAddress("glTexCoordP1uiv"));
	glTexCoordP1uiv(type,coords);
}
glTexCoordP1uivCallback glTexCoordP1uiv = glTexCoordP1uivDispatcher;

void glTexCoordP2uiDispatcher(GLenum type,GLuint coords){
	glTexCoordP2ui = reinterpret_cast<glTexCoordP2uiCallback>(OpenGLGetProcAddress("glTexCoordP2ui"));
	glTexCoordP2ui(type,coords);
}
glTexCoordP2uiCallback glTexCoordP2ui = glTexCoordP2uiDispatcher;

void glTexCoordP2uivDispatcher(GLenum type,const GLuint * coords){
	glTexCoordP2uiv = reinterpret_cast<glTexCoordP2uivCallback>(OpenGLGetProcAddress("glTexCoordP2uiv"));
	glTexCoordP2uiv(type,coords);
}
glTexCoordP2uivCallback glTexCoordP2uiv = glTexCoordP2uivDispatcher;

void glTexCoordP3uiDispatcher(GLenum type,GLuint coords){
	glTexCoordP3ui = reinterpret_cast<glTexCoordP3uiCallback>(OpenGLGetProcAddress("glTexCoordP3ui"));
	glTexCoordP3ui(type,coords);
}
glTexCoordP3uiCallback glTexCoordP3ui = glTexCoordP3uiDispatcher;

void glTexCoordP3uivDispatcher(GLenum type,const GLuint * coords){
	glTexCoordP3uiv = reinterpret_cast<glTexCoordP3uivCallback>(OpenGLGetProcAddress("glTexCoordP3uiv"));
	glTexCoordP3uiv(type,coords);
}
glTexCoordP3uivCallback glTexCoordP3uiv = glTexCoordP3uivDispatcher;

void glTexCoordP4uiDispatcher(GLenum type,GLuint coords){
	glTexCoordP4ui = reinterpret_cast<glTexCoordP4uiCallback>(OpenGLGetProcAddress("glTexCoordP4ui"));
	glTexCoordP4ui(type,coords);
}
glTexCoordP4uiCallback glTexCoordP4ui = glTexCoordP4uiDispatcher;

void glTexCoordP4uivDispatcher(GLenum type,const GLuint * coords){
	glTexCoordP4uiv = reinterpret_cast<glTexCoordP4uivCallback>(OpenGLGetProcAddress("glTexCoordP4uiv"));
	glTexCoordP4uiv(type,coords);
}
glTexCoordP4uivCallback glTexCoordP4uiv = glTexCoordP4uivDispatcher;

void glTexCoordPointerDispatcher(GLint size,GLenum type,GLsizei stride,const void * pointer){
	glTexCoordPointer = reinterpret_cast<glTexCoordPointerCallback>(OpenGLGetProcAddress("glTexCoordPointer"));
	glTexCoordPointer(size,type,stride,pointer);
}
glTexCoordPointerCallback glTexCoordPointer = glTexCoordPointerDispatcher;

void glTexEnvfDispatcher(GLenum target,GLenum pname,GLfloat param){
	glTexEnvf = reinterpret_cast<glTexEnvfCallback>(OpenGLGetProcAddress("glTexEnvf"));
	glTexEnvf(target,pname,param);
}
glTexEnvfCallback glTexEnvf = glTexEnvfDispatcher;

void glTexEnvfvDispatcher(GLenum target,GLenum pname,const GLfloat * params){
	glTexEnvfv = reinterpret_cast<glTexEnvfvCallback>(OpenGLGetProcAddress("glTexEnvfv"));
	glTexEnvfv(target,pname,params);
}
glTexEnvfvCallback glTexEnvfv = glTexEnvfvDispatcher;

void glTexEnviDispatcher(GLenum target,GLenum pname,GLint param){
	glTexEnvi = reinterpret_cast<glTexEnviCallback>(OpenGLGetProcAddress("glTexEnvi"));
	glTexEnvi(target,pname,param);
}
glTexEnviCallback glTexEnvi = glTexEnviDispatcher;

void glTexEnvivDispatcher(GLenum target,GLenum pname,const GLint * params){
	glTexEnviv = reinterpret_cast<glTexEnvivCallback>(OpenGLGetProcAddress("glTexEnviv"));
	glTexEnviv(target,pname,params);
}
glTexEnvivCallback glTexEnviv = glTexEnvivDispatcher;

void glTexGendDispatcher(GLenum coord,GLenum pname,GLdouble param){
	glTexGend = reinterpret_cast<glTexGendCallback>(OpenGLGetProcAddress("glTexGend"));
	glTexGend(coord,pname,param);
}
glTexGendCallback glTexGend = glTexGendDispatcher;

void glTexGendvDispatcher(GLenum coord,GLenum pname,const GLdouble * params){
	glTexGendv = reinterpret_cast<glTexGendvCallback>(OpenGLGetProcAddress("glTexGendv"));
	glTexGendv(coord,pname,params);
}
glTexGendvCallback glTexGendv = glTexGendvDispatcher;

void glTexGenfDispatcher(GLenum coord,GLenum pname,GLfloat param){
	glTexGenf = reinterpret_cast<glTexGenfCallback>(OpenGLGetProcAddress("glTexGenf"));
	glTexGenf(coord,pname,param);
}
glTexGenfCallback glTexGenf = glTexGenfDispatcher;

void glTexGenfvDispatcher(GLenum coord,GLenum pname,const GLfloat * params){
	glTexGenfv = reinterpret_cast<glTexGenfvCallback>(OpenGLGetProcAddress("glTexGenfv"));
	glTexGenfv(coord,pname,params);
}
glTexGenfvCallback glTexGenfv = glTexGenfvDispatcher;

void glTexGeniDispatcher(GLenum coord,GLenum pname,GLint param){
	glTexGeni = reinterpret_cast<glTexGeniCallback>(OpenGLGetProcAddress("glTexGeni"));
	glTexGeni(coord,pname,param);
}
glTexGeniCallback glTexGeni = glTexGeniDispatcher;

void glTexGenivDispatcher(GLenum coord,GLenum pname,const GLint * params){
	glTexGeniv = reinterpret_cast<glTexGenivCallback>(OpenGLGetProcAddress("glTexGeniv"));
	glTexGeniv(coord,pname,params);
}
glTexGenivCallback glTexGeniv = glTexGenivDispatcher;

void glTexImage1DDispatcher(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,const void * pixels){
	glTexImage1D = reinterpret_cast<glTexImage1DCallback>(OpenGLGetProcAddress("glTexImage1D"));
	glTexImage1D(target,level,internalformat,width,border,format,type,pixels);
}
glTexImage1DCallback glTexImage1D = glTexImage1DDispatcher;

void glTexImage2DDispatcher(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const void * pixels){
	glTexImage2D = reinterpret_cast<glTexImage2DCallback>(OpenGLGetProcAddress("glTexImage2D"));
	glTexImage2D(target,level,internalformat,width,height,border,format,type,pixels);
}
glTexImage2DCallback glTexImage2D = glTexImage2DDispatcher;

void glTexImage2DMultisampleDispatcher(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations){
	glTexImage2DMultisample = reinterpret_cast<glTexImage2DMultisampleCallback>(OpenGLGetProcAddress("glTexImage2DMultisample"));
	glTexImage2DMultisample(target,samples,internalformat,width,height,fixedsamplelocations);
}
glTexImage2DMultisampleCallback glTexImage2DMultisample = glTexImage2DMultisampleDispatcher;

void glTexImage3DDispatcher(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,const void * pixels){
	glTexImage3D = reinterpret_cast<glTexImage3DCallback>(OpenGLGetProcAddress("glTexImage3D"));
	glTexImage3D(target,level,internalformat,width,height,depth,border,format,type,pixels);
}
glTexImage3DCallback glTexImage3D = glTexImage3DDispatcher;

void glTexImage3DMultisampleDispatcher(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations){
	glTexImage3DMultisample = reinterpret_cast<glTexImage3DMultisampleCallback>(OpenGLGetProcAddress("glTexImage3DMultisample"));
	glTexImage3DMultisample(target,samples,internalformat,width,height,depth,fixedsamplelocations);
}
glTexImage3DMultisampleCallback glTexImage3DMultisample = glTexImage3DMultisampleDispatcher;

void glTexParameterIivDispatcher(GLenum target,GLenum pname,const GLint * params){
	glTexParameterIiv = reinterpret_cast<glTexParameterIivCallback>(OpenGLGetProcAddress("glTexParameterIiv"));
	glTexParameterIiv(target,pname,params);
}
glTexParameterIivCallback glTexParameterIiv = glTexParameterIivDispatcher;

void glTexParameterIuivDispatcher(GLenum target,GLenum pname,const GLuint * params){
	glTexParameterIuiv = reinterpret_cast<glTexParameterIuivCallback>(OpenGLGetProcAddress("glTexParameterIuiv"));
	glTexParameterIuiv(target,pname,params);
}
glTexParameterIuivCallback glTexParameterIuiv = glTexParameterIuivDispatcher;

void glTexParameterfDispatcher(GLenum target,GLenum pname,GLfloat param){
	glTexParameterf = reinterpret_cast<glTexParameterfCallback>(OpenGLGetProcAddress("glTexParameterf"));
	glTexParameterf(target,pname,param);
}
glTexParameterfCallback glTexParameterf = glTexParameterfDispatcher;

void glTexParameterfvDispatcher(GLenum target,GLenum pname,const GLfloat * params){
	glTexParameterfv = reinterpret_cast<glTexParameterfvCallback>(OpenGLGetProcAddress("glTexParameterfv"));
	glTexParameterfv(target,pname,params);
}
glTexParameterfvCallback glTexParameterfv = glTexParameterfvDispatcher;

void glTexParameteriDispatcher(GLenum target,GLenum pname,GLint param){
	glTexParameteri = reinterpret_cast<glTexParameteriCallback>(OpenGLGetProcAddress("glTexParameteri"));
	glTexParameteri(target,pname,param);
}
glTexParameteriCallback glTexParameteri = glTexParameteriDispatcher;

void glTexParameterivDispatcher(GLenum target,GLenum pname,const GLint * params){
	glTexParameteriv = reinterpret_cast<glTexParameterivCallback>(OpenGLGetProcAddress("glTexParameteriv"));
	glTexParameteriv(target,pname,params);
}
glTexParameterivCallback glTexParameteriv = glTexParameterivDispatcher;

void glTexStorage1DDispatcher(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width){
	glTexStorage1D = reinterpret_cast<glTexStorage1DCallback>(OpenGLGetProcAddress("glTexStorage1D"));
	glTexStorage1D(target,levels,internalformat,width);
}
glTexStorage1DCallback glTexStorage1D = glTexStorage1DDispatcher;

void glTexStorage2DDispatcher(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height){
	glTexStorage2D = reinterpret_cast<glTexStorage2DCallback>(OpenGLGetProcAddress("glTexStorage2D"));
	glTexStorage2D(target,levels,internalformat,width,height);
}
glTexStorage2DCallback glTexStorage2D = glTexStorage2DDispatcher;

void glTexStorage2DMultisampleDispatcher(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations){
	glTexStorage2DMultisample = reinterpret_cast<glTexStorage2DMultisampleCallback>(OpenGLGetProcAddress("glTexStorage2DMultisample"));
	glTexStorage2DMultisample(target,samples,internalformat,width,height,fixedsamplelocations);
}
glTexStorage2DMultisampleCallback glTexStorage2DMultisample = glTexStorage2DMultisampleDispatcher;

void glTexStorage3DDispatcher(GLenum target,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth){
	glTexStorage3D = reinterpret_cast<glTexStorage3DCallback>(OpenGLGetProcAddress("glTexStorage3D"));
	glTexStorage3D(target,levels,internalformat,width,height,depth);
}
glTexStorage3DCallback glTexStorage3D = glTexStorage3DDispatcher;

void glTexStorage3DMultisampleDispatcher(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations){
	glTexStorage3DMultisample = reinterpret_cast<glTexStorage3DMultisampleCallback>(OpenGLGetProcAddress("glTexStorage3DMultisample"));
	glTexStorage3DMultisample(target,samples,internalformat,width,height,depth,fixedsamplelocations);
}
glTexStorage3DMultisampleCallback glTexStorage3DMultisample = glTexStorage3DMultisampleDispatcher;

void glTexSubImage1DDispatcher(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void * pixels){
	glTexSubImage1D = reinterpret_cast<glTexSubImage1DCallback>(OpenGLGetProcAddress("glTexSubImage1D"));
	glTexSubImage1D(target,level,xoffset,width,format,type,pixels);
}
glTexSubImage1DCallback glTexSubImage1D = glTexSubImage1DDispatcher;

void glTexSubImage2DDispatcher(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * pixels){
	glTexSubImage2D = reinterpret_cast<glTexSubImage2DCallback>(OpenGLGetProcAddress("glTexSubImage2D"));
	glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels);
}
glTexSubImage2DCallback glTexSubImage2D = glTexSubImage2DDispatcher;

void glTexSubImage3DDispatcher(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void * pixels){
	glTexSubImage3D = reinterpret_cast<glTexSubImage3DCallback>(OpenGLGetProcAddress("glTexSubImage3D"));
	glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);
}
glTexSubImage3DCallback glTexSubImage3D = glTexSubImage3DDispatcher;

void glTextureBarrierDispatcher(){
	glTextureBarrier = reinterpret_cast<glTextureBarrierCallback>(OpenGLGetProcAddress("glTextureBarrier"));
	glTextureBarrier();
}
glTextureBarrierCallback glTextureBarrier = glTextureBarrierDispatcher;

void glTextureBufferDispatcher(GLuint texture,GLenum internalformat,GLuint buffer){
	glTextureBuffer = reinterpret_cast<glTextureBufferCallback>(OpenGLGetProcAddress("glTextureBuffer"));
	glTextureBuffer(texture,internalformat,buffer);
}
glTextureBufferCallback glTextureBuffer = glTextureBufferDispatcher;

void glTextureBufferRangeDispatcher(GLuint texture,GLenum internalformat,GLuint buffer,GLintptr offset,GLsizei size){
	glTextureBufferRange = reinterpret_cast<glTextureBufferRangeCallback>(OpenGLGetProcAddress("glTextureBufferRange"));
	glTextureBufferRange(texture,internalformat,buffer,offset,size);
}
glTextureBufferRangeCallback glTextureBufferRange = glTextureBufferRangeDispatcher;

void glTextureParameterIivDispatcher(GLuint texture,GLenum pname,const GLint * params){
	glTextureParameterIiv = reinterpret_cast<glTextureParameterIivCallback>(OpenGLGetProcAddress("glTextureParameterIiv"));
	glTextureParameterIiv(texture,pname,params);
}
glTextureParameterIivCallback glTextureParameterIiv = glTextureParameterIivDispatcher;

void glTextureParameterIuivDispatcher(GLuint texture,GLenum pname,const GLuint * params){
	glTextureParameterIuiv = reinterpret_cast<glTextureParameterIuivCallback>(OpenGLGetProcAddress("glTextureParameterIuiv"));
	glTextureParameterIuiv(texture,pname,params);
}
glTextureParameterIuivCallback glTextureParameterIuiv = glTextureParameterIuivDispatcher;

void glTextureParameterfDispatcher(GLuint texture,GLenum pname,GLfloat param){
	glTextureParameterf = reinterpret_cast<glTextureParameterfCallback>(OpenGLGetProcAddress("glTextureParameterf"));
	glTextureParameterf(texture,pname,param);
}
glTextureParameterfCallback glTextureParameterf = glTextureParameterfDispatcher;

void glTextureParameterfvDispatcher(GLuint texture,GLenum pname,const GLfloat * param){
	glTextureParameterfv = reinterpret_cast<glTextureParameterfvCallback>(OpenGLGetProcAddress("glTextureParameterfv"));
	glTextureParameterfv(texture,pname,param);
}
glTextureParameterfvCallback glTextureParameterfv = glTextureParameterfvDispatcher;

void glTextureParameteriDispatcher(GLuint texture,GLenum pname,GLint param){
	glTextureParameteri = reinterpret_cast<glTextureParameteriCallback>(OpenGLGetProcAddress("glTextureParameteri"));
	glTextureParameteri(texture,pname,param);
}
glTextureParameteriCallback glTextureParameteri = glTextureParameteriDispatcher;

void glTextureParameterivDispatcher(GLuint texture,GLenum pname,const GLint * param){
	glTextureParameteriv = reinterpret_cast<glTextureParameterivCallback>(OpenGLGetProcAddress("glTextureParameteriv"));
	glTextureParameteriv(texture,pname,param);
}
glTextureParameterivCallback glTextureParameteriv = glTextureParameterivDispatcher;

void glTextureStorage1DDispatcher(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width){
	glTextureStorage1D = reinterpret_cast<glTextureStorage1DCallback>(OpenGLGetProcAddress("glTextureStorage1D"));
	glTextureStorage1D(texture,levels,internalformat,width);
}
glTextureStorage1DCallback glTextureStorage1D = glTextureStorage1DDispatcher;

void glTextureStorage2DDispatcher(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height){
	glTextureStorage2D = reinterpret_cast<glTextureStorage2DCallback>(OpenGLGetProcAddress("glTextureStorage2D"));
	glTextureStorage2D(texture,levels,internalformat,width,height);
}
glTextureStorage2DCallback glTextureStorage2D = glTextureStorage2DDispatcher;

void glTextureStorage2DMultisampleDispatcher(GLuint texture,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations){
	glTextureStorage2DMultisample = reinterpret_cast<glTextureStorage2DMultisampleCallback>(OpenGLGetProcAddress("glTextureStorage2DMultisample"));
	glTextureStorage2DMultisample(texture,samples,internalformat,width,height,fixedsamplelocations);
}
glTextureStorage2DMultisampleCallback glTextureStorage2DMultisample = glTextureStorage2DMultisampleDispatcher;

void glTextureStorage3DDispatcher(GLuint texture,GLsizei levels,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth){
	glTextureStorage3D = reinterpret_cast<glTextureStorage3DCallback>(OpenGLGetProcAddress("glTextureStorage3D"));
	glTextureStorage3D(texture,levels,internalformat,width,height,depth);
}
glTextureStorage3DCallback glTextureStorage3D = glTextureStorage3DDispatcher;

void glTextureStorage3DMultisampleDispatcher(GLuint texture,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations){
	glTextureStorage3DMultisample = reinterpret_cast<glTextureStorage3DMultisampleCallback>(OpenGLGetProcAddress("glTextureStorage3DMultisample"));
	glTextureStorage3DMultisample(texture,samples,internalformat,width,height,depth,fixedsamplelocations);
}
glTextureStorage3DMultisampleCallback glTextureStorage3DMultisample = glTextureStorage3DMultisampleDispatcher;

void glTextureSubImage1DDispatcher(GLuint texture,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const void * pixels){
	glTextureSubImage1D = reinterpret_cast<glTextureSubImage1DCallback>(OpenGLGetProcAddress("glTextureSubImage1D"));
	glTextureSubImage1D(texture,level,xoffset,width,format,type,pixels);
}
glTextureSubImage1DCallback glTextureSubImage1D = glTextureSubImage1DDispatcher;

void glTextureSubImage2DDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * pixels){
	glTextureSubImage2D = reinterpret_cast<glTextureSubImage2DCallback>(OpenGLGetProcAddress("glTextureSubImage2D"));
	glTextureSubImage2D(texture,level,xoffset,yoffset,width,height,format,type,pixels);
}
glTextureSubImage2DCallback glTextureSubImage2D = glTextureSubImage2DDispatcher;

void glTextureSubImage3DDispatcher(GLuint texture,GLint level,GLint xoffset,GLint yoffset,GLint zoffset,GLsizei width,GLsizei height,GLsizei depth,GLenum format,GLenum type,const void * pixels){
	glTextureSubImage3D = reinterpret_cast<glTextureSubImage3DCallback>(OpenGLGetProcAddress("glTextureSubImage3D"));
	glTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);
}
glTextureSubImage3DCallback glTextureSubImage3D = glTextureSubImage3DDispatcher;

void glTextureViewDispatcher(GLuint texture,GLenum target,GLuint origtexture,GLenum internalformat,GLuint minlevel,GLuint numlevels,GLuint minlayer,GLuint numlayers){
	glTextureView = reinterpret_cast<glTextureViewCallback>(OpenGLGetProcAddress("glTextureView"));
	glTextureView(texture,target,origtexture,internalformat,minlevel,numlevels,minlayer,numlayers);
}
glTextureViewCallback glTextureView = glTextureViewDispatcher;

void glTransformFeedbackBufferBaseDispatcher(GLuint xfb,GLuint index,GLuint buffer){
	glTransformFeedbackBufferBase = reinterpret_cast<glTransformFeedbackBufferBaseCallback>(OpenGLGetProcAddress("glTransformFeedbackBufferBase"));
	glTransformFeedbackBufferBase(xfb,index,buffer);
}
glTransformFeedbackBufferBaseCallback glTransformFeedbackBufferBase = glTransformFeedbackBufferBaseDispatcher;

void glTransformFeedbackBufferRangeDispatcher(GLuint xfb,GLuint index,GLuint buffer,GLintptr offset,GLsizei size){
	glTransformFeedbackBufferRange = reinterpret_cast<glTransformFeedbackBufferRangeCallback>(OpenGLGetProcAddress("glTransformFeedbackBufferRange"));
	glTransformFeedbackBufferRange(xfb,index,buffer,offset,size);
}
glTransformFeedbackBufferRangeCallback glTransformFeedbackBufferRange = glTransformFeedbackBufferRangeDispatcher;

void glTransformFeedbackVaryingsDispatcher(GLuint program,GLsizei count,const GLchar *const* varyings,GLenum bufferMode){
	glTransformFeedbackVaryings = reinterpret_cast<glTransformFeedbackVaryingsCallback>(OpenGLGetProcAddress("glTransformFeedbackVaryings"));
	glTransformFeedbackVaryings(program,count,varyings,bufferMode);
}
glTransformFeedbackVaryingsCallback glTransformFeedbackVaryings = glTransformFeedbackVaryingsDispatcher;

void glTranslatedDispatcher(GLdouble x,GLdouble y,GLdouble z){
	glTranslated = reinterpret_cast<glTranslatedCallback>(OpenGLGetProcAddress("glTranslated"));
	glTranslated(x,y,z);
}
glTranslatedCallback glTranslated = glTranslatedDispatcher;

void glTranslatefDispatcher(GLfloat x,GLfloat y,GLfloat z){
	glTranslatef = reinterpret_cast<glTranslatefCallback>(OpenGLGetProcAddress("glTranslatef"));
	glTranslatef(x,y,z);
}
glTranslatefCallback glTranslatef = glTranslatefDispatcher;

void glUniform1dDispatcher(GLint location,GLdouble x){
	glUniform1d = reinterpret_cast<glUniform1dCallback>(OpenGLGetProcAddress("glUniform1d"));
	glUniform1d(location,x);
}
glUniform1dCallback glUniform1d = glUniform1dDispatcher;

void glUniform1dvDispatcher(GLint location,GLsizei count,const GLdouble * value){
	glUniform1dv = reinterpret_cast<glUniform1dvCallback>(OpenGLGetProcAddress("glUniform1dv"));
	glUniform1dv(location,count,value);
}
glUniform1dvCallback glUniform1dv = glUniform1dvDispatcher;

void glUniform1fDispatcher(GLint location,GLfloat v0){
	glUniform1f = reinterpret_cast<glUniform1fCallback>(OpenGLGetProcAddress("glUniform1f"));
	glUniform1f(location,v0);
}
glUniform1fCallback glUniform1f = glUniform1fDispatcher;

void glUniform1fvDispatcher(GLint location,GLsizei count,const GLfloat * value){
	glUniform1fv = reinterpret_cast<glUniform1fvCallback>(OpenGLGetProcAddress("glUniform1fv"));
	glUniform1fv(location,count,value);
}
glUniform1fvCallback glUniform1fv = glUniform1fvDispatcher;

void glUniform1iDispatcher(GLint location,GLint v0){
	glUniform1i = reinterpret_cast<glUniform1iCallback>(OpenGLGetProcAddress("glUniform1i"));
	glUniform1i(location,v0);
}
glUniform1iCallback glUniform1i = glUniform1iDispatcher;

void glUniform1ivDispatcher(GLint location,GLsizei count,const GLint * value){
	glUniform1iv = reinterpret_cast<glUniform1ivCallback>(OpenGLGetProcAddress("glUniform1iv"));
	glUniform1iv(location,count,value);
}
glUniform1ivCallback glUniform1iv = glUniform1ivDispatcher;

void glUniform1uiDispatcher(GLint location,GLuint v0){
	glUniform1ui = reinterpret_cast<glUniform1uiCallback>(OpenGLGetProcAddress("glUniform1ui"));
	glUniform1ui(location,v0);
}
glUniform1uiCallback glUniform1ui = glUniform1uiDispatcher;

void glUniform1uivDispatcher(GLint location,GLsizei count,const GLuint * value){
	glUniform1uiv = reinterpret_cast<glUniform1uivCallback>(OpenGLGetProcAddress("glUniform1uiv"));
	glUniform1uiv(location,count,value);
}
glUniform1uivCallback glUniform1uiv = glUniform1uivDispatcher;

void glUniform2dDispatcher(GLint location,GLdouble x,GLdouble y){
	glUniform2d = reinterpret_cast<glUniform2dCallback>(OpenGLGetProcAddress("glUniform2d"));
	glUniform2d(location,x,y);
}
glUniform2dCallback glUniform2d = glUniform2dDispatcher;

void glUniform2dvDispatcher(GLint location,GLsizei count,const GLdouble * value){
	glUniform2dv = reinterpret_cast<glUniform2dvCallback>(OpenGLGetProcAddress("glUniform2dv"));
	glUniform2dv(location,count,value);
}
glUniform2dvCallback glUniform2dv = glUniform2dvDispatcher;

void glUniform2fDispatcher(GLint location,GLfloat v0,GLfloat v1){
	glUniform2f = reinterpret_cast<glUniform2fCallback>(OpenGLGetProcAddress("glUniform2f"));
	glUniform2f(location,v0,v1);
}
glUniform2fCallback glUniform2f = glUniform2fDispatcher;

void glUniform2fvDispatcher(GLint location,GLsizei count,const GLfloat * value){
	glUniform2fv = reinterpret_cast<glUniform2fvCallback>(OpenGLGetProcAddress("glUniform2fv"));
	glUniform2fv(location,count,value);
}
glUniform2fvCallback glUniform2fv = glUniform2fvDispatcher;

void glUniform2iDispatcher(GLint location,GLint v0,GLint v1){
	glUniform2i = reinterpret_cast<glUniform2iCallback>(OpenGLGetProcAddress("glUniform2i"));
	glUniform2i(location,v0,v1);
}
glUniform2iCallback glUniform2i = glUniform2iDispatcher;

void glUniform2ivDispatcher(GLint location,GLsizei count,const GLint * value){
	glUniform2iv = reinterpret_cast<glUniform2ivCallback>(OpenGLGetProcAddress("glUniform2iv"));
	glUniform2iv(location,count,value);
}
glUniform2ivCallback glUniform2iv = glUniform2ivDispatcher;

void glUniform2uiDispatcher(GLint location,GLuint v0,GLuint v1){
	glUniform2ui = reinterpret_cast<glUniform2uiCallback>(OpenGLGetProcAddress("glUniform2ui"));
	glUniform2ui(location,v0,v1);
}
glUniform2uiCallback glUniform2ui = glUniform2uiDispatcher;

void glUniform2uivDispatcher(GLint location,GLsizei count,const GLuint * value){
	glUniform2uiv = reinterpret_cast<glUniform2uivCallback>(OpenGLGetProcAddress("glUniform2uiv"));
	glUniform2uiv(location,count,value);
}
glUniform2uivCallback glUniform2uiv = glUniform2uivDispatcher;

void glUniform3dDispatcher(GLint location,GLdouble x,GLdouble y,GLdouble z){
	glUniform3d = reinterpret_cast<glUniform3dCallback>(OpenGLGetProcAddress("glUniform3d"));
	glUniform3d(location,x,y,z);
}
glUniform3dCallback glUniform3d = glUniform3dDispatcher;

void glUniform3dvDispatcher(GLint location,GLsizei count,const GLdouble * value){
	glUniform3dv = reinterpret_cast<glUniform3dvCallback>(OpenGLGetProcAddress("glUniform3dv"));
	glUniform3dv(location,count,value);
}
glUniform3dvCallback glUniform3dv = glUniform3dvDispatcher;

void glUniform3fDispatcher(GLint location,GLfloat v0,GLfloat v1,GLfloat v2){
	glUniform3f = reinterpret_cast<glUniform3fCallback>(OpenGLGetProcAddress("glUniform3f"));
	glUniform3f(location,v0,v1,v2);
}
glUniform3fCallback glUniform3f = glUniform3fDispatcher;

void glUniform3fvDispatcher(GLint location,GLsizei count,const GLfloat * value){
	glUniform3fv = reinterpret_cast<glUniform3fvCallback>(OpenGLGetProcAddress("glUniform3fv"));
	glUniform3fv(location,count,value);
}
glUniform3fvCallback glUniform3fv = glUniform3fvDispatcher;

void glUniform3iDispatcher(GLint location,GLint v0,GLint v1,GLint v2){
	glUniform3i = reinterpret_cast<glUniform3iCallback>(OpenGLGetProcAddress("glUniform3i"));
	glUniform3i(location,v0,v1,v2);
}
glUniform3iCallback glUniform3i = glUniform3iDispatcher;

void glUniform3ivDispatcher(GLint location,GLsizei count,const GLint * value){
	glUniform3iv = reinterpret_cast<glUniform3ivCallback>(OpenGLGetProcAddress("glUniform3iv"));
	glUniform3iv(location,count,value);
}
glUniform3ivCallback glUniform3iv = glUniform3ivDispatcher;

void glUniform3uiDispatcher(GLint location,GLuint v0,GLuint v1,GLuint v2){
	glUniform3ui = reinterpret_cast<glUniform3uiCallback>(OpenGLGetProcAddress("glUniform3ui"));
	glUniform3ui(location,v0,v1,v2);
}
glUniform3uiCallback glUniform3ui = glUniform3uiDispatcher;

void glUniform3uivDispatcher(GLint location,GLsizei count,const GLuint * value){
	glUniform3uiv = reinterpret_cast<glUniform3uivCallback>(OpenGLGetProcAddress("glUniform3uiv"));
	glUniform3uiv(location,count,value);
}
glUniform3uivCallback glUniform3uiv = glUniform3uivDispatcher;

void glUniform4dDispatcher(GLint location,GLdouble x,GLdouble y,GLdouble z,GLdouble w){
	glUniform4d = reinterpret_cast<glUniform4dCallback>(OpenGLGetProcAddress("glUniform4d"));
	glUniform4d(location,x,y,z,w);
}
glUniform4dCallback glUniform4d = glUniform4dDispatcher;

void glUniform4dvDispatcher(GLint location,GLsizei count,const GLdouble * value){
	glUniform4dv = reinterpret_cast<glUniform4dvCallback>(OpenGLGetProcAddress("glUniform4dv"));
	glUniform4dv(location,count,value);
}
glUniform4dvCallback glUniform4dv = glUniform4dvDispatcher;

void glUniform4fDispatcher(GLint location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3){
	glUniform4f = reinterpret_cast<glUniform4fCallback>(OpenGLGetProcAddress("glUniform4f"));
	glUniform4f(location,v0,v1,v2,v3);
}
glUniform4fCallback glUniform4f = glUniform4fDispatcher;

void glUniform4fvDispatcher(GLint location,GLsizei count,const GLfloat * value){
	glUniform4fv = reinterpret_cast<glUniform4fvCallback>(OpenGLGetProcAddress("glUniform4fv"));
	glUniform4fv(location,count,value);
}
glUniform4fvCallback glUniform4fv = glUniform4fvDispatcher;

void glUniform4iDispatcher(GLint location,GLint v0,GLint v1,GLint v2,GLint v3){
	glUniform4i = reinterpret_cast<glUniform4iCallback>(OpenGLGetProcAddress("glUniform4i"));
	glUniform4i(location,v0,v1,v2,v3);
}
glUniform4iCallback glUniform4i = glUniform4iDispatcher;

void glUniform4ivDispatcher(GLint location,GLsizei count,const GLint * value){
	glUniform4iv = reinterpret_cast<glUniform4ivCallback>(OpenGLGetProcAddress("glUniform4iv"));
	glUniform4iv(location,count,value);
}
glUniform4ivCallback glUniform4iv = glUniform4ivDispatcher;

void glUniform4uiDispatcher(GLint location,GLuint v0,GLuint v1,GLuint v2,GLuint v3){
	glUniform4ui = reinterpret_cast<glUniform4uiCallback>(OpenGLGetProcAddress("glUniform4ui"));
	glUniform4ui(location,v0,v1,v2,v3);
}
glUniform4uiCallback glUniform4ui = glUniform4uiDispatcher;

void glUniform4uivDispatcher(GLint location,GLsizei count,const GLuint * value){
	glUniform4uiv = reinterpret_cast<glUniform4uivCallback>(OpenGLGetProcAddress("glUniform4uiv"));
	glUniform4uiv(location,count,value);
}
glUniform4uivCallback glUniform4uiv = glUniform4uivDispatcher;

void glUniformBlockBindingDispatcher(GLuint program,GLuint uniformBlockIndex,GLuint uniformBlockBinding){
	glUniformBlockBinding = reinterpret_cast<glUniformBlockBindingCallback>(OpenGLGetProcAddress("glUniformBlockBinding"));
	glUniformBlockBinding(program,uniformBlockIndex,uniformBlockBinding);
}
glUniformBlockBindingCallback glUniformBlockBinding = glUniformBlockBindingDispatcher;

void glUniformMatrix2dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix2dv = reinterpret_cast<glUniformMatrix2dvCallback>(OpenGLGetProcAddress("glUniformMatrix2dv"));
	glUniformMatrix2dv(location,count,transpose,value);
}
glUniformMatrix2dvCallback glUniformMatrix2dv = glUniformMatrix2dvDispatcher;

void glUniformMatrix2fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix2fv = reinterpret_cast<glUniformMatrix2fvCallback>(OpenGLGetProcAddress("glUniformMatrix2fv"));
	glUniformMatrix2fv(location,count,transpose,value);
}
glUniformMatrix2fvCallback glUniformMatrix2fv = glUniformMatrix2fvDispatcher;

void glUniformMatrix2x3dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix2x3dv = reinterpret_cast<glUniformMatrix2x3dvCallback>(OpenGLGetProcAddress("glUniformMatrix2x3dv"));
	glUniformMatrix2x3dv(location,count,transpose,value);
}
glUniformMatrix2x3dvCallback glUniformMatrix2x3dv = glUniformMatrix2x3dvDispatcher;

void glUniformMatrix2x3fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix2x3fv = reinterpret_cast<glUniformMatrix2x3fvCallback>(OpenGLGetProcAddress("glUniformMatrix2x3fv"));
	glUniformMatrix2x3fv(location,count,transpose,value);
}
glUniformMatrix2x3fvCallback glUniformMatrix2x3fv = glUniformMatrix2x3fvDispatcher;

void glUniformMatrix2x4dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix2x4dv = reinterpret_cast<glUniformMatrix2x4dvCallback>(OpenGLGetProcAddress("glUniformMatrix2x4dv"));
	glUniformMatrix2x4dv(location,count,transpose,value);
}
glUniformMatrix2x4dvCallback glUniformMatrix2x4dv = glUniformMatrix2x4dvDispatcher;

void glUniformMatrix2x4fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix2x4fv = reinterpret_cast<glUniformMatrix2x4fvCallback>(OpenGLGetProcAddress("glUniformMatrix2x4fv"));
	glUniformMatrix2x4fv(location,count,transpose,value);
}
glUniformMatrix2x4fvCallback glUniformMatrix2x4fv = glUniformMatrix2x4fvDispatcher;

void glUniformMatrix3dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix3dv = reinterpret_cast<glUniformMatrix3dvCallback>(OpenGLGetProcAddress("glUniformMatrix3dv"));
	glUniformMatrix3dv(location,count,transpose,value);
}
glUniformMatrix3dvCallback glUniformMatrix3dv = glUniformMatrix3dvDispatcher;

void glUniformMatrix3fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix3fv = reinterpret_cast<glUniformMatrix3fvCallback>(OpenGLGetProcAddress("glUniformMatrix3fv"));
	glUniformMatrix3fv(location,count,transpose,value);
}
glUniformMatrix3fvCallback glUniformMatrix3fv = glUniformMatrix3fvDispatcher;

void glUniformMatrix3x2dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix3x2dv = reinterpret_cast<glUniformMatrix3x2dvCallback>(OpenGLGetProcAddress("glUniformMatrix3x2dv"));
	glUniformMatrix3x2dv(location,count,transpose,value);
}
glUniformMatrix3x2dvCallback glUniformMatrix3x2dv = glUniformMatrix3x2dvDispatcher;

void glUniformMatrix3x2fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix3x2fv = reinterpret_cast<glUniformMatrix3x2fvCallback>(OpenGLGetProcAddress("glUniformMatrix3x2fv"));
	glUniformMatrix3x2fv(location,count,transpose,value);
}
glUniformMatrix3x2fvCallback glUniformMatrix3x2fv = glUniformMatrix3x2fvDispatcher;

void glUniformMatrix3x4dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix3x4dv = reinterpret_cast<glUniformMatrix3x4dvCallback>(OpenGLGetProcAddress("glUniformMatrix3x4dv"));
	glUniformMatrix3x4dv(location,count,transpose,value);
}
glUniformMatrix3x4dvCallback glUniformMatrix3x4dv = glUniformMatrix3x4dvDispatcher;

void glUniformMatrix3x4fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix3x4fv = reinterpret_cast<glUniformMatrix3x4fvCallback>(OpenGLGetProcAddress("glUniformMatrix3x4fv"));
	glUniformMatrix3x4fv(location,count,transpose,value);
}
glUniformMatrix3x4fvCallback glUniformMatrix3x4fv = glUniformMatrix3x4fvDispatcher;

void glUniformMatrix4dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix4dv = reinterpret_cast<glUniformMatrix4dvCallback>(OpenGLGetProcAddress("glUniformMatrix4dv"));
	glUniformMatrix4dv(location,count,transpose,value);
}
glUniformMatrix4dvCallback glUniformMatrix4dv = glUniformMatrix4dvDispatcher;

void glUniformMatrix4fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix4fv = reinterpret_cast<glUniformMatrix4fvCallback>(OpenGLGetProcAddress("glUniformMatrix4fv"));
	glUniformMatrix4fv(location,count,transpose,value);
}
glUniformMatrix4fvCallback glUniformMatrix4fv = glUniformMatrix4fvDispatcher;

void glUniformMatrix4x2dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix4x2dv = reinterpret_cast<glUniformMatrix4x2dvCallback>(OpenGLGetProcAddress("glUniformMatrix4x2dv"));
	glUniformMatrix4x2dv(location,count,transpose,value);
}
glUniformMatrix4x2dvCallback glUniformMatrix4x2dv = glUniformMatrix4x2dvDispatcher;

void glUniformMatrix4x2fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix4x2fv = reinterpret_cast<glUniformMatrix4x2fvCallback>(OpenGLGetProcAddress("glUniformMatrix4x2fv"));
	glUniformMatrix4x2fv(location,count,transpose,value);
}
glUniformMatrix4x2fvCallback glUniformMatrix4x2fv = glUniformMatrix4x2fvDispatcher;

void glUniformMatrix4x3dvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLdouble * value){
	glUniformMatrix4x3dv = reinterpret_cast<glUniformMatrix4x3dvCallback>(OpenGLGetProcAddress("glUniformMatrix4x3dv"));
	glUniformMatrix4x3dv(location,count,transpose,value);
}
glUniformMatrix4x3dvCallback glUniformMatrix4x3dv = glUniformMatrix4x3dvDispatcher;

void glUniformMatrix4x3fvDispatcher(GLint location,GLsizei count,GLboolean transpose,const GLfloat * value){
	glUniformMatrix4x3fv = reinterpret_cast<glUniformMatrix4x3fvCallback>(OpenGLGetProcAddress("glUniformMatrix4x3fv"));
	glUniformMatrix4x3fv(location,count,transpose,value);
}
glUniformMatrix4x3fvCallback glUniformMatrix4x3fv = glUniformMatrix4x3fvDispatcher;

void glUniformSubroutinesuivDispatcher(GLenum shadertype,GLsizei count,const GLuint * indices){
	glUniformSubroutinesuiv = reinterpret_cast<glUniformSubroutinesuivCallback>(OpenGLGetProcAddress("glUniformSubroutinesuiv"));
	glUniformSubroutinesuiv(shadertype,count,indices);
}
glUniformSubroutinesuivCallback glUniformSubroutinesuiv = glUniformSubroutinesuivDispatcher;

GLboolean glUnmapBufferDispatcher(GLenum target){
	glUnmapBuffer = reinterpret_cast<glUnmapBufferCallback>(OpenGLGetProcAddress("glUnmapBuffer"));
	return 	glUnmapBuffer(target);
}
glUnmapBufferCallback glUnmapBuffer = glUnmapBufferDispatcher;

GLboolean glUnmapNamedBufferDispatcher(GLuint buffer){
	glUnmapNamedBuffer = reinterpret_cast<glUnmapNamedBufferCallback>(OpenGLGetProcAddress("glUnmapNamedBuffer"));
	return 	glUnmapNamedBuffer(buffer);
}
glUnmapNamedBufferCallback glUnmapNamedBuffer = glUnmapNamedBufferDispatcher;

void glUseProgramDispatcher(GLuint program){
	glUseProgram = reinterpret_cast<glUseProgramCallback>(OpenGLGetProcAddress("glUseProgram"));
	glUseProgram(program);
}
glUseProgramCallback glUseProgram = glUseProgramDispatcher;

void glUseProgramStagesDispatcher(GLuint pipeline,GLbitfield stages,GLuint program){
	glUseProgramStages = reinterpret_cast<glUseProgramStagesCallback>(OpenGLGetProcAddress("glUseProgramStages"));
	glUseProgramStages(pipeline,stages,program);
}
glUseProgramStagesCallback glUseProgramStages = glUseProgramStagesDispatcher;

void glValidateProgramDispatcher(GLuint program){
	glValidateProgram = reinterpret_cast<glValidateProgramCallback>(OpenGLGetProcAddress("glValidateProgram"));
	glValidateProgram(program);
}
glValidateProgramCallback glValidateProgram = glValidateProgramDispatcher;

void glValidateProgramPipelineDispatcher(GLuint pipeline){
	glValidateProgramPipeline = reinterpret_cast<glValidateProgramPipelineCallback>(OpenGLGetProcAddress("glValidateProgramPipeline"));
	glValidateProgramPipeline(pipeline);
}
glValidateProgramPipelineCallback glValidateProgramPipeline = glValidateProgramPipelineDispatcher;

void glVertex2dDispatcher(GLdouble x,GLdouble y){
	glVertex2d = reinterpret_cast<glVertex2dCallback>(OpenGLGetProcAddress("glVertex2d"));
	glVertex2d(x,y);
}
glVertex2dCallback glVertex2d = glVertex2dDispatcher;

void glVertex2dvDispatcher(const GLdouble * v){
	glVertex2dv = reinterpret_cast<glVertex2dvCallback>(OpenGLGetProcAddress("glVertex2dv"));
	glVertex2dv(v);
}
glVertex2dvCallback glVertex2dv = glVertex2dvDispatcher;

void glVertex2fDispatcher(GLfloat x,GLfloat y){
	glVertex2f = reinterpret_cast<glVertex2fCallback>(OpenGLGetProcAddress("glVertex2f"));
	glVertex2f(x,y);
}
glVertex2fCallback glVertex2f = glVertex2fDispatcher;

void glVertex2fvDispatcher(const GLfloat * v){
	glVertex2fv = reinterpret_cast<glVertex2fvCallback>(OpenGLGetProcAddress("glVertex2fv"));
	glVertex2fv(v);
}
glVertex2fvCallback glVertex2fv = glVertex2fvDispatcher;

void glVertex2iDispatcher(GLint x,GLint y){
	glVertex2i = reinterpret_cast<glVertex2iCallback>(OpenGLGetProcAddress("glVertex2i"));
	glVertex2i(x,y);
}
glVertex2iCallback glVertex2i = glVertex2iDispatcher;

void glVertex2ivDispatcher(const GLint * v){
	glVertex2iv = reinterpret_cast<glVertex2ivCallback>(OpenGLGetProcAddress("glVertex2iv"));
	glVertex2iv(v);
}
glVertex2ivCallback glVertex2iv = glVertex2ivDispatcher;

void glVertex2sDispatcher(GLshort x,GLshort y){
	glVertex2s = reinterpret_cast<glVertex2sCallback>(OpenGLGetProcAddress("glVertex2s"));
	glVertex2s(x,y);
}
glVertex2sCallback glVertex2s = glVertex2sDispatcher;

void glVertex2svDispatcher(const GLshort * v){
	glVertex2sv = reinterpret_cast<glVertex2svCallback>(OpenGLGetProcAddress("glVertex2sv"));
	glVertex2sv(v);
}
glVertex2svCallback glVertex2sv = glVertex2svDispatcher;

void glVertex3dDispatcher(GLdouble x,GLdouble y,GLdouble z){
	glVertex3d = reinterpret_cast<glVertex3dCallback>(OpenGLGetProcAddress("glVertex3d"));
	glVertex3d(x,y,z);
}
glVertex3dCallback glVertex3d = glVertex3dDispatcher;

void glVertex3dvDispatcher(const GLdouble * v){
	glVertex3dv = reinterpret_cast<glVertex3dvCallback>(OpenGLGetProcAddress("glVertex3dv"));
	glVertex3dv(v);
}
glVertex3dvCallback glVertex3dv = glVertex3dvDispatcher;

void glVertex3fDispatcher(GLfloat x,GLfloat y,GLfloat z){
	glVertex3f = reinterpret_cast<glVertex3fCallback>(OpenGLGetProcAddress("glVertex3f"));
	glVertex3f(x,y,z);
}
glVertex3fCallback glVertex3f = glVertex3fDispatcher;

void glVertex3fvDispatcher(const GLfloat * v){
	glVertex3fv = reinterpret_cast<glVertex3fvCallback>(OpenGLGetProcAddress("glVertex3fv"));
	glVertex3fv(v);
}
glVertex3fvCallback glVertex3fv = glVertex3fvDispatcher;

void glVertex3iDispatcher(GLint x,GLint y,GLint z){
	glVertex3i = reinterpret_cast<glVertex3iCallback>(OpenGLGetProcAddress("glVertex3i"));
	glVertex3i(x,y,z);
}
glVertex3iCallback glVertex3i = glVertex3iDispatcher;

void glVertex3ivDispatcher(const GLint * v){
	glVertex3iv = reinterpret_cast<glVertex3ivCallback>(OpenGLGetProcAddress("glVertex3iv"));
	glVertex3iv(v);
}
glVertex3ivCallback glVertex3iv = glVertex3ivDispatcher;

void glVertex3sDispatcher(GLshort x,GLshort y,GLshort z){
	glVertex3s = reinterpret_cast<glVertex3sCallback>(OpenGLGetProcAddress("glVertex3s"));
	glVertex3s(x,y,z);
}
glVertex3sCallback glVertex3s = glVertex3sDispatcher;

void glVertex3svDispatcher(const GLshort * v){
	glVertex3sv = reinterpret_cast<glVertex3svCallback>(OpenGLGetProcAddress("glVertex3sv"));
	glVertex3sv(v);
}
glVertex3svCallback glVertex3sv = glVertex3svDispatcher;

void glVertex4dDispatcher(GLdouble x,GLdouble y,GLdouble z,GLdouble w){
	glVertex4d = reinterpret_cast<glVertex4dCallback>(OpenGLGetProcAddress("glVertex4d"));
	glVertex4d(x,y,z,w);
}
glVertex4dCallback glVertex4d = glVertex4dDispatcher;

void glVertex4dvDispatcher(const GLdouble * v){
	glVertex4dv = reinterpret_cast<glVertex4dvCallback>(OpenGLGetProcAddress("glVertex4dv"));
	glVertex4dv(v);
}
glVertex4dvCallback glVertex4dv = glVertex4dvDispatcher;

void glVertex4fDispatcher(GLfloat x,GLfloat y,GLfloat z,GLfloat w){
	glVertex4f = reinterpret_cast<glVertex4fCallback>(OpenGLGetProcAddress("glVertex4f"));
	glVertex4f(x,y,z,w);
}
glVertex4fCallback glVertex4f = glVertex4fDispatcher;

void glVertex4fvDispatcher(const GLfloat * v){
	glVertex4fv = reinterpret_cast<glVertex4fvCallback>(OpenGLGetProcAddress("glVertex4fv"));
	glVertex4fv(v);
}
glVertex4fvCallback glVertex4fv = glVertex4fvDispatcher;

void glVertex4iDispatcher(GLint x,GLint y,GLint z,GLint w){
	glVertex4i = reinterpret_cast<glVertex4iCallback>(OpenGLGetProcAddress("glVertex4i"));
	glVertex4i(x,y,z,w);
}
glVertex4iCallback glVertex4i = glVertex4iDispatcher;

void glVertex4ivDispatcher(const GLint * v){
	glVertex4iv = reinterpret_cast<glVertex4ivCallback>(OpenGLGetProcAddress("glVertex4iv"));
	glVertex4iv(v);
}
glVertex4ivCallback glVertex4iv = glVertex4ivDispatcher;

void glVertex4sDispatcher(GLshort x,GLshort y,GLshort z,GLshort w){
	glVertex4s = reinterpret_cast<glVertex4sCallback>(OpenGLGetProcAddress("glVertex4s"));
	glVertex4s(x,y,z,w);
}
glVertex4sCallback glVertex4s = glVertex4sDispatcher;

void glVertex4svDispatcher(const GLshort * v){
	glVertex4sv = reinterpret_cast<glVertex4svCallback>(OpenGLGetProcAddress("glVertex4sv"));
	glVertex4sv(v);
}
glVertex4svCallback glVertex4sv = glVertex4svDispatcher;

void glVertexArrayAttribBindingDispatcher(GLuint vaobj,GLuint attribindex,GLuint bindingindex){
	glVertexArrayAttribBinding = reinterpret_cast<glVertexArrayAttribBindingCallback>(OpenGLGetProcAddress("glVertexArrayAttribBinding"));
	glVertexArrayAttribBinding(vaobj,attribindex,bindingindex);
}
glVertexArrayAttribBindingCallback glVertexArrayAttribBinding = glVertexArrayAttribBindingDispatcher;

void glVertexArrayAttribFormatDispatcher(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset){
	glVertexArrayAttribFormat = reinterpret_cast<glVertexArrayAttribFormatCallback>(OpenGLGetProcAddress("glVertexArrayAttribFormat"));
	glVertexArrayAttribFormat(vaobj,attribindex,size,type,normalized,relativeoffset);
}
glVertexArrayAttribFormatCallback glVertexArrayAttribFormat = glVertexArrayAttribFormatDispatcher;

void glVertexArrayAttribIFormatDispatcher(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){
	glVertexArrayAttribIFormat = reinterpret_cast<glVertexArrayAttribIFormatCallback>(OpenGLGetProcAddress("glVertexArrayAttribIFormat"));
	glVertexArrayAttribIFormat(vaobj,attribindex,size,type,relativeoffset);
}
glVertexArrayAttribIFormatCallback glVertexArrayAttribIFormat = glVertexArrayAttribIFormatDispatcher;

void glVertexArrayAttribLFormatDispatcher(GLuint vaobj,GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){
	glVertexArrayAttribLFormat = reinterpret_cast<glVertexArrayAttribLFormatCallback>(OpenGLGetProcAddress("glVertexArrayAttribLFormat"));
	glVertexArrayAttribLFormat(vaobj,attribindex,size,type,relativeoffset);
}
glVertexArrayAttribLFormatCallback glVertexArrayAttribLFormat = glVertexArrayAttribLFormatDispatcher;

void glVertexArrayBindingDivisorDispatcher(GLuint vaobj,GLuint bindingindex,GLuint divisor){
	glVertexArrayBindingDivisor = reinterpret_cast<glVertexArrayBindingDivisorCallback>(OpenGLGetProcAddress("glVertexArrayBindingDivisor"));
	glVertexArrayBindingDivisor(vaobj,bindingindex,divisor);
}
glVertexArrayBindingDivisorCallback glVertexArrayBindingDivisor = glVertexArrayBindingDivisorDispatcher;

void glVertexArrayElementBufferDispatcher(GLuint vaobj,GLuint buffer){
	glVertexArrayElementBuffer = reinterpret_cast<glVertexArrayElementBufferCallback>(OpenGLGetProcAddress("glVertexArrayElementBuffer"));
	glVertexArrayElementBuffer(vaobj,buffer);
}
glVertexArrayElementBufferCallback glVertexArrayElementBuffer = glVertexArrayElementBufferDispatcher;

void glVertexArrayVertexBufferDispatcher(GLuint vaobj,GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride){
	glVertexArrayVertexBuffer = reinterpret_cast<glVertexArrayVertexBufferCallback>(OpenGLGetProcAddress("glVertexArrayVertexBuffer"));
	glVertexArrayVertexBuffer(vaobj,bindingindex,buffer,offset,stride);
}
glVertexArrayVertexBufferCallback glVertexArrayVertexBuffer = glVertexArrayVertexBufferDispatcher;

void glVertexArrayVertexBuffersDispatcher(GLuint vaobj,GLuint first,GLsizei count,const GLuint * buffers,const GLintptr * offsets,const GLsizei * strides){
	glVertexArrayVertexBuffers = reinterpret_cast<glVertexArrayVertexBuffersCallback>(OpenGLGetProcAddress("glVertexArrayVertexBuffers"));
	glVertexArrayVertexBuffers(vaobj,first,count,buffers,offsets,strides);
}
glVertexArrayVertexBuffersCallback glVertexArrayVertexBuffers = glVertexArrayVertexBuffersDispatcher;

void glVertexAttrib1dDispatcher(GLuint index,GLdouble x){
	glVertexAttrib1d = reinterpret_cast<glVertexAttrib1dCallback>(OpenGLGetProcAddress("glVertexAttrib1d"));
	glVertexAttrib1d(index,x);
}
glVertexAttrib1dCallback glVertexAttrib1d = glVertexAttrib1dDispatcher;

void glVertexAttrib1dvDispatcher(GLuint index,const GLdouble * v){
	glVertexAttrib1dv = reinterpret_cast<glVertexAttrib1dvCallback>(OpenGLGetProcAddress("glVertexAttrib1dv"));
	glVertexAttrib1dv(index,v);
}
glVertexAttrib1dvCallback glVertexAttrib1dv = glVertexAttrib1dvDispatcher;

void glVertexAttrib1fDispatcher(GLuint index,GLfloat x){
	glVertexAttrib1f = reinterpret_cast<glVertexAttrib1fCallback>(OpenGLGetProcAddress("glVertexAttrib1f"));
	glVertexAttrib1f(index,x);
}
glVertexAttrib1fCallback glVertexAttrib1f = glVertexAttrib1fDispatcher;

void glVertexAttrib1fvDispatcher(GLuint index,const GLfloat * v){
	glVertexAttrib1fv = reinterpret_cast<glVertexAttrib1fvCallback>(OpenGLGetProcAddress("glVertexAttrib1fv"));
	glVertexAttrib1fv(index,v);
}
glVertexAttrib1fvCallback glVertexAttrib1fv = glVertexAttrib1fvDispatcher;

void glVertexAttrib1sDispatcher(GLuint index,GLshort x){
	glVertexAttrib1s = reinterpret_cast<glVertexAttrib1sCallback>(OpenGLGetProcAddress("glVertexAttrib1s"));
	glVertexAttrib1s(index,x);
}
glVertexAttrib1sCallback glVertexAttrib1s = glVertexAttrib1sDispatcher;

void glVertexAttrib1svDispatcher(GLuint index,const GLshort * v){
	glVertexAttrib1sv = reinterpret_cast<glVertexAttrib1svCallback>(OpenGLGetProcAddress("glVertexAttrib1sv"));
	glVertexAttrib1sv(index,v);
}
glVertexAttrib1svCallback glVertexAttrib1sv = glVertexAttrib1svDispatcher;

void glVertexAttrib2dDispatcher(GLuint index,GLdouble x,GLdouble y){
	glVertexAttrib2d = reinterpret_cast<glVertexAttrib2dCallback>(OpenGLGetProcAddress("glVertexAttrib2d"));
	glVertexAttrib2d(index,x,y);
}
glVertexAttrib2dCallback glVertexAttrib2d = glVertexAttrib2dDispatcher;

void glVertexAttrib2dvDispatcher(GLuint index,const GLdouble * v){
	glVertexAttrib2dv = reinterpret_cast<glVertexAttrib2dvCallback>(OpenGLGetProcAddress("glVertexAttrib2dv"));
	glVertexAttrib2dv(index,v);
}
glVertexAttrib2dvCallback glVertexAttrib2dv = glVertexAttrib2dvDispatcher;

void glVertexAttrib2fDispatcher(GLuint index,GLfloat x,GLfloat y){
	glVertexAttrib2f = reinterpret_cast<glVertexAttrib2fCallback>(OpenGLGetProcAddress("glVertexAttrib2f"));
	glVertexAttrib2f(index,x,y);
}
glVertexAttrib2fCallback glVertexAttrib2f = glVertexAttrib2fDispatcher;

void glVertexAttrib2fvDispatcher(GLuint index,const GLfloat * v){
	glVertexAttrib2fv = reinterpret_cast<glVertexAttrib2fvCallback>(OpenGLGetProcAddress("glVertexAttrib2fv"));
	glVertexAttrib2fv(index,v);
}
glVertexAttrib2fvCallback glVertexAttrib2fv = glVertexAttrib2fvDispatcher;

void glVertexAttrib2sDispatcher(GLuint index,GLshort x,GLshort y){
	glVertexAttrib2s = reinterpret_cast<glVertexAttrib2sCallback>(OpenGLGetProcAddress("glVertexAttrib2s"));
	glVertexAttrib2s(index,x,y);
}
glVertexAttrib2sCallback glVertexAttrib2s = glVertexAttrib2sDispatcher;

void glVertexAttrib2svDispatcher(GLuint index,const GLshort * v){
	glVertexAttrib2sv = reinterpret_cast<glVertexAttrib2svCallback>(OpenGLGetProcAddress("glVertexAttrib2sv"));
	glVertexAttrib2sv(index,v);
}
glVertexAttrib2svCallback glVertexAttrib2sv = glVertexAttrib2svDispatcher;

void glVertexAttrib3dDispatcher(GLuint index,GLdouble x,GLdouble y,GLdouble z){
	glVertexAttrib3d = reinterpret_cast<glVertexAttrib3dCallback>(OpenGLGetProcAddress("glVertexAttrib3d"));
	glVertexAttrib3d(index,x,y,z);
}
glVertexAttrib3dCallback glVertexAttrib3d = glVertexAttrib3dDispatcher;

void glVertexAttrib3dvDispatcher(GLuint index,const GLdouble * v){
	glVertexAttrib3dv = reinterpret_cast<glVertexAttrib3dvCallback>(OpenGLGetProcAddress("glVertexAttrib3dv"));
	glVertexAttrib3dv(index,v);
}
glVertexAttrib3dvCallback glVertexAttrib3dv = glVertexAttrib3dvDispatcher;

void glVertexAttrib3fDispatcher(GLuint index,GLfloat x,GLfloat y,GLfloat z){
	glVertexAttrib3f = reinterpret_cast<glVertexAttrib3fCallback>(OpenGLGetProcAddress("glVertexAttrib3f"));
	glVertexAttrib3f(index,x,y,z);
}
glVertexAttrib3fCallback glVertexAttrib3f = glVertexAttrib3fDispatcher;

void glVertexAttrib3fvDispatcher(GLuint index,const GLfloat * v){
	glVertexAttrib3fv = reinterpret_cast<glVertexAttrib3fvCallback>(OpenGLGetProcAddress("glVertexAttrib3fv"));
	glVertexAttrib3fv(index,v);
}
glVertexAttrib3fvCallback glVertexAttrib3fv = glVertexAttrib3fvDispatcher;

void glVertexAttrib3sDispatcher(GLuint index,GLshort x,GLshort y,GLshort z){
	glVertexAttrib3s = reinterpret_cast<glVertexAttrib3sCallback>(OpenGLGetProcAddress("glVertexAttrib3s"));
	glVertexAttrib3s(index,x,y,z);
}
glVertexAttrib3sCallback glVertexAttrib3s = glVertexAttrib3sDispatcher;

void glVertexAttrib3svDispatcher(GLuint index,const GLshort * v){
	glVertexAttrib3sv = reinterpret_cast<glVertexAttrib3svCallback>(OpenGLGetProcAddress("glVertexAttrib3sv"));
	glVertexAttrib3sv(index,v);
}
glVertexAttrib3svCallback glVertexAttrib3sv = glVertexAttrib3svDispatcher;

void glVertexAttrib4NbvDispatcher(GLuint index,const GLbyte * v){
	glVertexAttrib4Nbv = reinterpret_cast<glVertexAttrib4NbvCallback>(OpenGLGetProcAddress("glVertexAttrib4Nbv"));
	glVertexAttrib4Nbv(index,v);
}
glVertexAttrib4NbvCallback glVertexAttrib4Nbv = glVertexAttrib4NbvDispatcher;

void glVertexAttrib4NivDispatcher(GLuint index,const GLint * v){
	glVertexAttrib4Niv = reinterpret_cast<glVertexAttrib4NivCallback>(OpenGLGetProcAddress("glVertexAttrib4Niv"));
	glVertexAttrib4Niv(index,v);
}
glVertexAttrib4NivCallback glVertexAttrib4Niv = glVertexAttrib4NivDispatcher;

void glVertexAttrib4NsvDispatcher(GLuint index,const GLshort * v){
	glVertexAttrib4Nsv = reinterpret_cast<glVertexAttrib4NsvCallback>(OpenGLGetProcAddress("glVertexAttrib4Nsv"));
	glVertexAttrib4Nsv(index,v);
}
glVertexAttrib4NsvCallback glVertexAttrib4Nsv = glVertexAttrib4NsvDispatcher;

void glVertexAttrib4NubDispatcher(GLuint index,GLubyte x,GLubyte y,GLubyte z,GLubyte w){
	glVertexAttrib4Nub = reinterpret_cast<glVertexAttrib4NubCallback>(OpenGLGetProcAddress("glVertexAttrib4Nub"));
	glVertexAttrib4Nub(index,x,y,z,w);
}
glVertexAttrib4NubCallback glVertexAttrib4Nub = glVertexAttrib4NubDispatcher;

void glVertexAttrib4NubvDispatcher(GLuint index,const GLubyte * v){
	glVertexAttrib4Nubv = reinterpret_cast<glVertexAttrib4NubvCallback>(OpenGLGetProcAddress("glVertexAttrib4Nubv"));
	glVertexAttrib4Nubv(index,v);
}
glVertexAttrib4NubvCallback glVertexAttrib4Nubv = glVertexAttrib4NubvDispatcher;

void glVertexAttrib4NuivDispatcher(GLuint index,const GLuint * v){
	glVertexAttrib4Nuiv = reinterpret_cast<glVertexAttrib4NuivCallback>(OpenGLGetProcAddress("glVertexAttrib4Nuiv"));
	glVertexAttrib4Nuiv(index,v);
}
glVertexAttrib4NuivCallback glVertexAttrib4Nuiv = glVertexAttrib4NuivDispatcher;

void glVertexAttrib4NusvDispatcher(GLuint index,const GLushort * v){
	glVertexAttrib4Nusv = reinterpret_cast<glVertexAttrib4NusvCallback>(OpenGLGetProcAddress("glVertexAttrib4Nusv"));
	glVertexAttrib4Nusv(index,v);
}
glVertexAttrib4NusvCallback glVertexAttrib4Nusv = glVertexAttrib4NusvDispatcher;

void glVertexAttrib4bvDispatcher(GLuint index,const GLbyte * v){
	glVertexAttrib4bv = reinterpret_cast<glVertexAttrib4bvCallback>(OpenGLGetProcAddress("glVertexAttrib4bv"));
	glVertexAttrib4bv(index,v);
}
glVertexAttrib4bvCallback glVertexAttrib4bv = glVertexAttrib4bvDispatcher;

void glVertexAttrib4dDispatcher(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){
	glVertexAttrib4d = reinterpret_cast<glVertexAttrib4dCallback>(OpenGLGetProcAddress("glVertexAttrib4d"));
	glVertexAttrib4d(index,x,y,z,w);
}
glVertexAttrib4dCallback glVertexAttrib4d = glVertexAttrib4dDispatcher;

void glVertexAttrib4dvDispatcher(GLuint index,const GLdouble * v){
	glVertexAttrib4dv = reinterpret_cast<glVertexAttrib4dvCallback>(OpenGLGetProcAddress("glVertexAttrib4dv"));
	glVertexAttrib4dv(index,v);
}
glVertexAttrib4dvCallback glVertexAttrib4dv = glVertexAttrib4dvDispatcher;

void glVertexAttrib4fDispatcher(GLuint index,GLfloat x,GLfloat y,GLfloat z,GLfloat w){
	glVertexAttrib4f = reinterpret_cast<glVertexAttrib4fCallback>(OpenGLGetProcAddress("glVertexAttrib4f"));
	glVertexAttrib4f(index,x,y,z,w);
}
glVertexAttrib4fCallback glVertexAttrib4f = glVertexAttrib4fDispatcher;

void glVertexAttrib4fvDispatcher(GLuint index,const GLfloat * v){
	glVertexAttrib4fv = reinterpret_cast<glVertexAttrib4fvCallback>(OpenGLGetProcAddress("glVertexAttrib4fv"));
	glVertexAttrib4fv(index,v);
}
glVertexAttrib4fvCallback glVertexAttrib4fv = glVertexAttrib4fvDispatcher;

void glVertexAttrib4ivDispatcher(GLuint index,const GLint * v){
	glVertexAttrib4iv = reinterpret_cast<glVertexAttrib4ivCallback>(OpenGLGetProcAddress("glVertexAttrib4iv"));
	glVertexAttrib4iv(index,v);
}
glVertexAttrib4ivCallback glVertexAttrib4iv = glVertexAttrib4ivDispatcher;

void glVertexAttrib4sDispatcher(GLuint index,GLshort x,GLshort y,GLshort z,GLshort w){
	glVertexAttrib4s = reinterpret_cast<glVertexAttrib4sCallback>(OpenGLGetProcAddress("glVertexAttrib4s"));
	glVertexAttrib4s(index,x,y,z,w);
}
glVertexAttrib4sCallback glVertexAttrib4s = glVertexAttrib4sDispatcher;

void glVertexAttrib4svDispatcher(GLuint index,const GLshort * v){
	glVertexAttrib4sv = reinterpret_cast<glVertexAttrib4svCallback>(OpenGLGetProcAddress("glVertexAttrib4sv"));
	glVertexAttrib4sv(index,v);
}
glVertexAttrib4svCallback glVertexAttrib4sv = glVertexAttrib4svDispatcher;

void glVertexAttrib4ubvDispatcher(GLuint index,const GLubyte * v){
	glVertexAttrib4ubv = reinterpret_cast<glVertexAttrib4ubvCallback>(OpenGLGetProcAddress("glVertexAttrib4ubv"));
	glVertexAttrib4ubv(index,v);
}
glVertexAttrib4ubvCallback glVertexAttrib4ubv = glVertexAttrib4ubvDispatcher;

void glVertexAttrib4uivDispatcher(GLuint index,const GLuint * v){
	glVertexAttrib4uiv = reinterpret_cast<glVertexAttrib4uivCallback>(OpenGLGetProcAddress("glVertexAttrib4uiv"));
	glVertexAttrib4uiv(index,v);
}
glVertexAttrib4uivCallback glVertexAttrib4uiv = glVertexAttrib4uivDispatcher;

void glVertexAttrib4usvDispatcher(GLuint index,const GLushort * v){
	glVertexAttrib4usv = reinterpret_cast<glVertexAttrib4usvCallback>(OpenGLGetProcAddress("glVertexAttrib4usv"));
	glVertexAttrib4usv(index,v);
}
glVertexAttrib4usvCallback glVertexAttrib4usv = glVertexAttrib4usvDispatcher;

void glVertexAttribBindingDispatcher(GLuint attribindex,GLuint bindingindex){
	glVertexAttribBinding = reinterpret_cast<glVertexAttribBindingCallback>(OpenGLGetProcAddress("glVertexAttribBinding"));
	glVertexAttribBinding(attribindex,bindingindex);
}
glVertexAttribBindingCallback glVertexAttribBinding = glVertexAttribBindingDispatcher;

void glVertexAttribDivisorDispatcher(GLuint index,GLuint divisor){
	glVertexAttribDivisor = reinterpret_cast<glVertexAttribDivisorCallback>(OpenGLGetProcAddress("glVertexAttribDivisor"));
	glVertexAttribDivisor(index,divisor);
}
glVertexAttribDivisorCallback glVertexAttribDivisor = glVertexAttribDivisorDispatcher;

void glVertexAttribFormatDispatcher(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset){
	glVertexAttribFormat = reinterpret_cast<glVertexAttribFormatCallback>(OpenGLGetProcAddress("glVertexAttribFormat"));
	glVertexAttribFormat(attribindex,size,type,normalized,relativeoffset);
}
glVertexAttribFormatCallback glVertexAttribFormat = glVertexAttribFormatDispatcher;

void glVertexAttribI1iDispatcher(GLuint index,GLint x){
	glVertexAttribI1i = reinterpret_cast<glVertexAttribI1iCallback>(OpenGLGetProcAddress("glVertexAttribI1i"));
	glVertexAttribI1i(index,x);
}
glVertexAttribI1iCallback glVertexAttribI1i = glVertexAttribI1iDispatcher;

void glVertexAttribI1ivDispatcher(GLuint index,const GLint * v){
	glVertexAttribI1iv = reinterpret_cast<glVertexAttribI1ivCallback>(OpenGLGetProcAddress("glVertexAttribI1iv"));
	glVertexAttribI1iv(index,v);
}
glVertexAttribI1ivCallback glVertexAttribI1iv = glVertexAttribI1ivDispatcher;

void glVertexAttribI1uiDispatcher(GLuint index,GLuint x){
	glVertexAttribI1ui = reinterpret_cast<glVertexAttribI1uiCallback>(OpenGLGetProcAddress("glVertexAttribI1ui"));
	glVertexAttribI1ui(index,x);
}
glVertexAttribI1uiCallback glVertexAttribI1ui = glVertexAttribI1uiDispatcher;

void glVertexAttribI1uivDispatcher(GLuint index,const GLuint * v){
	glVertexAttribI1uiv = reinterpret_cast<glVertexAttribI1uivCallback>(OpenGLGetProcAddress("glVertexAttribI1uiv"));
	glVertexAttribI1uiv(index,v);
}
glVertexAttribI1uivCallback glVertexAttribI1uiv = glVertexAttribI1uivDispatcher;

void glVertexAttribI2iDispatcher(GLuint index,GLint x,GLint y){
	glVertexAttribI2i = reinterpret_cast<glVertexAttribI2iCallback>(OpenGLGetProcAddress("glVertexAttribI2i"));
	glVertexAttribI2i(index,x,y);
}
glVertexAttribI2iCallback glVertexAttribI2i = glVertexAttribI2iDispatcher;

void glVertexAttribI2ivDispatcher(GLuint index,const GLint * v){
	glVertexAttribI2iv = reinterpret_cast<glVertexAttribI2ivCallback>(OpenGLGetProcAddress("glVertexAttribI2iv"));
	glVertexAttribI2iv(index,v);
}
glVertexAttribI2ivCallback glVertexAttribI2iv = glVertexAttribI2ivDispatcher;

void glVertexAttribI2uiDispatcher(GLuint index,GLuint x,GLuint y){
	glVertexAttribI2ui = reinterpret_cast<glVertexAttribI2uiCallback>(OpenGLGetProcAddress("glVertexAttribI2ui"));
	glVertexAttribI2ui(index,x,y);
}
glVertexAttribI2uiCallback glVertexAttribI2ui = glVertexAttribI2uiDispatcher;

void glVertexAttribI2uivDispatcher(GLuint index,const GLuint * v){
	glVertexAttribI2uiv = reinterpret_cast<glVertexAttribI2uivCallback>(OpenGLGetProcAddress("glVertexAttribI2uiv"));
	glVertexAttribI2uiv(index,v);
}
glVertexAttribI2uivCallback glVertexAttribI2uiv = glVertexAttribI2uivDispatcher;

void glVertexAttribI3iDispatcher(GLuint index,GLint x,GLint y,GLint z){
	glVertexAttribI3i = reinterpret_cast<glVertexAttribI3iCallback>(OpenGLGetProcAddress("glVertexAttribI3i"));
	glVertexAttribI3i(index,x,y,z);
}
glVertexAttribI3iCallback glVertexAttribI3i = glVertexAttribI3iDispatcher;

void glVertexAttribI3ivDispatcher(GLuint index,const GLint * v){
	glVertexAttribI3iv = reinterpret_cast<glVertexAttribI3ivCallback>(OpenGLGetProcAddress("glVertexAttribI3iv"));
	glVertexAttribI3iv(index,v);
}
glVertexAttribI3ivCallback glVertexAttribI3iv = glVertexAttribI3ivDispatcher;

void glVertexAttribI3uiDispatcher(GLuint index,GLuint x,GLuint y,GLuint z){
	glVertexAttribI3ui = reinterpret_cast<glVertexAttribI3uiCallback>(OpenGLGetProcAddress("glVertexAttribI3ui"));
	glVertexAttribI3ui(index,x,y,z);
}
glVertexAttribI3uiCallback glVertexAttribI3ui = glVertexAttribI3uiDispatcher;

void glVertexAttribI3uivDispatcher(GLuint index,const GLuint * v){
	glVertexAttribI3uiv = reinterpret_cast<glVertexAttribI3uivCallback>(OpenGLGetProcAddress("glVertexAttribI3uiv"));
	glVertexAttribI3uiv(index,v);
}
glVertexAttribI3uivCallback glVertexAttribI3uiv = glVertexAttribI3uivDispatcher;

void glVertexAttribI4bvDispatcher(GLuint index,const GLbyte * v){
	glVertexAttribI4bv = reinterpret_cast<glVertexAttribI4bvCallback>(OpenGLGetProcAddress("glVertexAttribI4bv"));
	glVertexAttribI4bv(index,v);
}
glVertexAttribI4bvCallback glVertexAttribI4bv = glVertexAttribI4bvDispatcher;

void glVertexAttribI4iDispatcher(GLuint index,GLint x,GLint y,GLint z,GLint w){
	glVertexAttribI4i = reinterpret_cast<glVertexAttribI4iCallback>(OpenGLGetProcAddress("glVertexAttribI4i"));
	glVertexAttribI4i(index,x,y,z,w);
}
glVertexAttribI4iCallback glVertexAttribI4i = glVertexAttribI4iDispatcher;

void glVertexAttribI4ivDispatcher(GLuint index,const GLint * v){
	glVertexAttribI4iv = reinterpret_cast<glVertexAttribI4ivCallback>(OpenGLGetProcAddress("glVertexAttribI4iv"));
	glVertexAttribI4iv(index,v);
}
glVertexAttribI4ivCallback glVertexAttribI4iv = glVertexAttribI4ivDispatcher;

void glVertexAttribI4svDispatcher(GLuint index,const GLshort * v){
	glVertexAttribI4sv = reinterpret_cast<glVertexAttribI4svCallback>(OpenGLGetProcAddress("glVertexAttribI4sv"));
	glVertexAttribI4sv(index,v);
}
glVertexAttribI4svCallback glVertexAttribI4sv = glVertexAttribI4svDispatcher;

void glVertexAttribI4ubvDispatcher(GLuint index,const GLubyte * v){
	glVertexAttribI4ubv = reinterpret_cast<glVertexAttribI4ubvCallback>(OpenGLGetProcAddress("glVertexAttribI4ubv"));
	glVertexAttribI4ubv(index,v);
}
glVertexAttribI4ubvCallback glVertexAttribI4ubv = glVertexAttribI4ubvDispatcher;

void glVertexAttribI4uiDispatcher(GLuint index,GLuint x,GLuint y,GLuint z,GLuint w){
	glVertexAttribI4ui = reinterpret_cast<glVertexAttribI4uiCallback>(OpenGLGetProcAddress("glVertexAttribI4ui"));
	glVertexAttribI4ui(index,x,y,z,w);
}
glVertexAttribI4uiCallback glVertexAttribI4ui = glVertexAttribI4uiDispatcher;

void glVertexAttribI4uivDispatcher(GLuint index,const GLuint * v){
	glVertexAttribI4uiv = reinterpret_cast<glVertexAttribI4uivCallback>(OpenGLGetProcAddress("glVertexAttribI4uiv"));
	glVertexAttribI4uiv(index,v);
}
glVertexAttribI4uivCallback glVertexAttribI4uiv = glVertexAttribI4uivDispatcher;

void glVertexAttribI4usvDispatcher(GLuint index,const GLushort * v){
	glVertexAttribI4usv = reinterpret_cast<glVertexAttribI4usvCallback>(OpenGLGetProcAddress("glVertexAttribI4usv"));
	glVertexAttribI4usv(index,v);
}
glVertexAttribI4usvCallback glVertexAttribI4usv = glVertexAttribI4usvDispatcher;

void glVertexAttribIFormatDispatcher(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){
	glVertexAttribIFormat = reinterpret_cast<glVertexAttribIFormatCallback>(OpenGLGetProcAddress("glVertexAttribIFormat"));
	glVertexAttribIFormat(attribindex,size,type,relativeoffset);
}
glVertexAttribIFormatCallback glVertexAttribIFormat = glVertexAttribIFormatDispatcher;

void glVertexAttribIPointerDispatcher(GLuint index,GLint size,GLenum type,GLsizei stride,const void * pointer){
	glVertexAttribIPointer = reinterpret_cast<glVertexAttribIPointerCallback>(OpenGLGetProcAddress("glVertexAttribIPointer"));
	glVertexAttribIPointer(index,size,type,stride,pointer);
}
glVertexAttribIPointerCallback glVertexAttribIPointer = glVertexAttribIPointerDispatcher;

void glVertexAttribL1dDispatcher(GLuint index,GLdouble x){
	glVertexAttribL1d = reinterpret_cast<glVertexAttribL1dCallback>(OpenGLGetProcAddress("glVertexAttribL1d"));
	glVertexAttribL1d(index,x);
}
glVertexAttribL1dCallback glVertexAttribL1d = glVertexAttribL1dDispatcher;

void glVertexAttribL1dvDispatcher(GLuint index,const GLdouble * v){
	glVertexAttribL1dv = reinterpret_cast<glVertexAttribL1dvCallback>(OpenGLGetProcAddress("glVertexAttribL1dv"));
	glVertexAttribL1dv(index,v);
}
glVertexAttribL1dvCallback glVertexAttribL1dv = glVertexAttribL1dvDispatcher;

void glVertexAttribL2dDispatcher(GLuint index,GLdouble x,GLdouble y){
	glVertexAttribL2d = reinterpret_cast<glVertexAttribL2dCallback>(OpenGLGetProcAddress("glVertexAttribL2d"));
	glVertexAttribL2d(index,x,y);
}
glVertexAttribL2dCallback glVertexAttribL2d = glVertexAttribL2dDispatcher;

void glVertexAttribL2dvDispatcher(GLuint index,const GLdouble * v){
	glVertexAttribL2dv = reinterpret_cast<glVertexAttribL2dvCallback>(OpenGLGetProcAddress("glVertexAttribL2dv"));
	glVertexAttribL2dv(index,v);
}
glVertexAttribL2dvCallback glVertexAttribL2dv = glVertexAttribL2dvDispatcher;

void glVertexAttribL3dDispatcher(GLuint index,GLdouble x,GLdouble y,GLdouble z){
	glVertexAttribL3d = reinterpret_cast<glVertexAttribL3dCallback>(OpenGLGetProcAddress("glVertexAttribL3d"));
	glVertexAttribL3d(index,x,y,z);
}
glVertexAttribL3dCallback glVertexAttribL3d = glVertexAttribL3dDispatcher;

void glVertexAttribL3dvDispatcher(GLuint index,const GLdouble * v){
	glVertexAttribL3dv = reinterpret_cast<glVertexAttribL3dvCallback>(OpenGLGetProcAddress("glVertexAttribL3dv"));
	glVertexAttribL3dv(index,v);
}
glVertexAttribL3dvCallback glVertexAttribL3dv = glVertexAttribL3dvDispatcher;

void glVertexAttribL4dDispatcher(GLuint index,GLdouble x,GLdouble y,GLdouble z,GLdouble w){
	glVertexAttribL4d = reinterpret_cast<glVertexAttribL4dCallback>(OpenGLGetProcAddress("glVertexAttribL4d"));
	glVertexAttribL4d(index,x,y,z,w);
}
glVertexAttribL4dCallback glVertexAttribL4d = glVertexAttribL4dDispatcher;

void glVertexAttribL4dvDispatcher(GLuint index,const GLdouble * v){
	glVertexAttribL4dv = reinterpret_cast<glVertexAttribL4dvCallback>(OpenGLGetProcAddress("glVertexAttribL4dv"));
	glVertexAttribL4dv(index,v);
}
glVertexAttribL4dvCallback glVertexAttribL4dv = glVertexAttribL4dvDispatcher;

void glVertexAttribLFormatDispatcher(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset){
	glVertexAttribLFormat = reinterpret_cast<glVertexAttribLFormatCallback>(OpenGLGetProcAddress("glVertexAttribLFormat"));
	glVertexAttribLFormat(attribindex,size,type,relativeoffset);
}
glVertexAttribLFormatCallback glVertexAttribLFormat = glVertexAttribLFormatDispatcher;

void glVertexAttribLPointerDispatcher(GLuint index,GLint size,GLenum type,GLsizei stride,const void * pointer){
	glVertexAttribLPointer = reinterpret_cast<glVertexAttribLPointerCallback>(OpenGLGetProcAddress("glVertexAttribLPointer"));
	glVertexAttribLPointer(index,size,type,stride,pointer);
}
glVertexAttribLPointerCallback glVertexAttribLPointer = glVertexAttribLPointerDispatcher;

void glVertexAttribP1uiDispatcher(GLuint index,GLenum type,GLboolean normalized,GLuint value){
	glVertexAttribP1ui = reinterpret_cast<glVertexAttribP1uiCallback>(OpenGLGetProcAddress("glVertexAttribP1ui"));
	glVertexAttribP1ui(index,type,normalized,value);
}
glVertexAttribP1uiCallback glVertexAttribP1ui = glVertexAttribP1uiDispatcher;

void glVertexAttribP1uivDispatcher(GLuint index,GLenum type,GLboolean normalized,const GLuint * value){
	glVertexAttribP1uiv = reinterpret_cast<glVertexAttribP1uivCallback>(OpenGLGetProcAddress("glVertexAttribP1uiv"));
	glVertexAttribP1uiv(index,type,normalized,value);
}
glVertexAttribP1uivCallback glVertexAttribP1uiv = glVertexAttribP1uivDispatcher;

void glVertexAttribP2uiDispatcher(GLuint index,GLenum type,GLboolean normalized,GLuint value){
	glVertexAttribP2ui = reinterpret_cast<glVertexAttribP2uiCallback>(OpenGLGetProcAddress("glVertexAttribP2ui"));
	glVertexAttribP2ui(index,type,normalized,value);
}
glVertexAttribP2uiCallback glVertexAttribP2ui = glVertexAttribP2uiDispatcher;

void glVertexAttribP2uivDispatcher(GLuint index,GLenum type,GLboolean normalized,const GLuint * value){
	glVertexAttribP2uiv = reinterpret_cast<glVertexAttribP2uivCallback>(OpenGLGetProcAddress("glVertexAttribP2uiv"));
	glVertexAttribP2uiv(index,type,normalized,value);
}
glVertexAttribP2uivCallback glVertexAttribP2uiv = glVertexAttribP2uivDispatcher;

void glVertexAttribP3uiDispatcher(GLuint index,GLenum type,GLboolean normalized,GLuint value){
	glVertexAttribP3ui = reinterpret_cast<glVertexAttribP3uiCallback>(OpenGLGetProcAddress("glVertexAttribP3ui"));
	glVertexAttribP3ui(index,type,normalized,value);
}
glVertexAttribP3uiCallback glVertexAttribP3ui = glVertexAttribP3uiDispatcher;

void glVertexAttribP3uivDispatcher(GLuint index,GLenum type,GLboolean normalized,const GLuint * value){
	glVertexAttribP3uiv = reinterpret_cast<glVertexAttribP3uivCallback>(OpenGLGetProcAddress("glVertexAttribP3uiv"));
	glVertexAttribP3uiv(index,type,normalized,value);
}
glVertexAttribP3uivCallback glVertexAttribP3uiv = glVertexAttribP3uivDispatcher;

void glVertexAttribP4uiDispatcher(GLuint index,GLenum type,GLboolean normalized,GLuint value){
	glVertexAttribP4ui = reinterpret_cast<glVertexAttribP4uiCallback>(OpenGLGetProcAddress("glVertexAttribP4ui"));
	glVertexAttribP4ui(index,type,normalized,value);
}
glVertexAttribP4uiCallback glVertexAttribP4ui = glVertexAttribP4uiDispatcher;

void glVertexAttribP4uivDispatcher(GLuint index,GLenum type,GLboolean normalized,const GLuint * value){
	glVertexAttribP4uiv = reinterpret_cast<glVertexAttribP4uivCallback>(OpenGLGetProcAddress("glVertexAttribP4uiv"));
	glVertexAttribP4uiv(index,type,normalized,value);
}
glVertexAttribP4uivCallback glVertexAttribP4uiv = glVertexAttribP4uivDispatcher;

void glVertexAttribPointerDispatcher(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,const void * pointer){
	glVertexAttribPointer = reinterpret_cast<glVertexAttribPointerCallback>(OpenGLGetProcAddress("glVertexAttribPointer"));
	glVertexAttribPointer(index,size,type,normalized,stride,pointer);
}
glVertexAttribPointerCallback glVertexAttribPointer = glVertexAttribPointerDispatcher;

void glVertexBindingDivisorDispatcher(GLuint bindingindex,GLuint divisor){
	glVertexBindingDivisor = reinterpret_cast<glVertexBindingDivisorCallback>(OpenGLGetProcAddress("glVertexBindingDivisor"));
	glVertexBindingDivisor(bindingindex,divisor);
}
glVertexBindingDivisorCallback glVertexBindingDivisor = glVertexBindingDivisorDispatcher;

void glVertexP2uiDispatcher(GLenum type,GLuint value){
	glVertexP2ui = reinterpret_cast<glVertexP2uiCallback>(OpenGLGetProcAddress("glVertexP2ui"));
	glVertexP2ui(type,value);
}
glVertexP2uiCallback glVertexP2ui = glVertexP2uiDispatcher;

void glVertexP2uivDispatcher(GLenum type,const GLuint * value){
	glVertexP2uiv = reinterpret_cast<glVertexP2uivCallback>(OpenGLGetProcAddress("glVertexP2uiv"));
	glVertexP2uiv(type,value);
}
glVertexP2uivCallback glVertexP2uiv = glVertexP2uivDispatcher;

void glVertexP3uiDispatcher(GLenum type,GLuint value){
	glVertexP3ui = reinterpret_cast<glVertexP3uiCallback>(OpenGLGetProcAddress("glVertexP3ui"));
	glVertexP3ui(type,value);
}
glVertexP3uiCallback glVertexP3ui = glVertexP3uiDispatcher;

void glVertexP3uivDispatcher(GLenum type,const GLuint * value){
	glVertexP3uiv = reinterpret_cast<glVertexP3uivCallback>(OpenGLGetProcAddress("glVertexP3uiv"));
	glVertexP3uiv(type,value);
}
glVertexP3uivCallback glVertexP3uiv = glVertexP3uivDispatcher;

void glVertexP4uiDispatcher(GLenum type,GLuint value){
	glVertexP4ui = reinterpret_cast<glVertexP4uiCallback>(OpenGLGetProcAddress("glVertexP4ui"));
	glVertexP4ui(type,value);
}
glVertexP4uiCallback glVertexP4ui = glVertexP4uiDispatcher;

void glVertexP4uivDispatcher(GLenum type,const GLuint * value){
	glVertexP4uiv = reinterpret_cast<glVertexP4uivCallback>(OpenGLGetProcAddress("glVertexP4uiv"));
	glVertexP4uiv(type,value);
}
glVertexP4uivCallback glVertexP4uiv = glVertexP4uivDispatcher;

void glVertexPointerDispatcher(GLint size,GLenum type,GLsizei stride,const void * pointer){
	glVertexPointer = reinterpret_cast<glVertexPointerCallback>(OpenGLGetProcAddress("glVertexPointer"));
	glVertexPointer(size,type,stride,pointer);
}
glVertexPointerCallback glVertexPointer = glVertexPointerDispatcher;

void glViewportDispatcher(GLint x,GLint y,GLsizei width,GLsizei height){
	glViewport = reinterpret_cast<glViewportCallback>(OpenGLGetProcAddress("glViewport"));
	glViewport(x,y,width,height);
}
glViewportCallback glViewport = glViewportDispatcher;

void glViewportArrayvDispatcher(GLuint first,GLsizei count,const GLfloat * v){
	glViewportArrayv = reinterpret_cast<glViewportArrayvCallback>(OpenGLGetProcAddress("glViewportArrayv"));
	glViewportArrayv(first,count,v);
}
glViewportArrayvCallback glViewportArrayv = glViewportArrayvDispatcher;

void glViewportIndexedfDispatcher(GLuint index,GLfloat x,GLfloat y,GLfloat w,GLfloat h){
	glViewportIndexedf = reinterpret_cast<glViewportIndexedfCallback>(OpenGLGetProcAddress("glViewportIndexedf"));
	glViewportIndexedf(index,x,y,w,h);
}
glViewportIndexedfCallback glViewportIndexedf = glViewportIndexedfDispatcher;

void glViewportIndexedfvDispatcher(GLuint index,const GLfloat * v){
	glViewportIndexedfv = reinterpret_cast<glViewportIndexedfvCallback>(OpenGLGetProcAddress("glViewportIndexedfv"));
	glViewportIndexedfv(index,v);
}
glViewportIndexedfvCallback glViewportIndexedfv = glViewportIndexedfvDispatcher;

void glWaitSyncDispatcher(GLsync sync,GLbitfield flags,GLuint64 timeout){
	glWaitSync = reinterpret_cast<glWaitSyncCallback>(OpenGLGetProcAddress("glWaitSync"));
	glWaitSync(sync,flags,timeout);
}
glWaitSyncCallback glWaitSync = glWaitSyncDispatcher;

void glWindowPos2dDispatcher(GLdouble x,GLdouble y){
	glWindowPos2d = reinterpret_cast<glWindowPos2dCallback>(OpenGLGetProcAddress("glWindowPos2d"));
	glWindowPos2d(x,y);
}
glWindowPos2dCallback glWindowPos2d = glWindowPos2dDispatcher;

void glWindowPos2dvDispatcher(const GLdouble * v){
	glWindowPos2dv = reinterpret_cast<glWindowPos2dvCallback>(OpenGLGetProcAddress("glWindowPos2dv"));
	glWindowPos2dv(v);
}
glWindowPos2dvCallback glWindowPos2dv = glWindowPos2dvDispatcher;

void glWindowPos2fDispatcher(GLfloat x,GLfloat y){
	glWindowPos2f = reinterpret_cast<glWindowPos2fCallback>(OpenGLGetProcAddress("glWindowPos2f"));
	glWindowPos2f(x,y);
}
glWindowPos2fCallback glWindowPos2f = glWindowPos2fDispatcher;

void glWindowPos2fvDispatcher(const GLfloat * v){
	glWindowPos2fv = reinterpret_cast<glWindowPos2fvCallback>(OpenGLGetProcAddress("glWindowPos2fv"));
	glWindowPos2fv(v);
}
glWindowPos2fvCallback glWindowPos2fv = glWindowPos2fvDispatcher;

void glWindowPos2iDispatcher(GLint x,GLint y){
	glWindowPos2i = reinterpret_cast<glWindowPos2iCallback>(OpenGLGetProcAddress("glWindowPos2i"));
	glWindowPos2i(x,y);
}
glWindowPos2iCallback glWindowPos2i = glWindowPos2iDispatcher;

void glWindowPos2ivDispatcher(const GLint * v){
	glWindowPos2iv = reinterpret_cast<glWindowPos2ivCallback>(OpenGLGetProcAddress("glWindowPos2iv"));
	glWindowPos2iv(v);
}
glWindowPos2ivCallback glWindowPos2iv = glWindowPos2ivDispatcher;

void glWindowPos2sDispatcher(GLshort x,GLshort y){
	glWindowPos2s = reinterpret_cast<glWindowPos2sCallback>(OpenGLGetProcAddress("glWindowPos2s"));
	glWindowPos2s(x,y);
}
glWindowPos2sCallback glWindowPos2s = glWindowPos2sDispatcher;

void glWindowPos2svDispatcher(const GLshort * v){
	glWindowPos2sv = reinterpret_cast<glWindowPos2svCallback>(OpenGLGetProcAddress("glWindowPos2sv"));
	glWindowPos2sv(v);
}
glWindowPos2svCallback glWindowPos2sv = glWindowPos2svDispatcher;

void glWindowPos3dDispatcher(GLdouble x,GLdouble y,GLdouble z){
	glWindowPos3d = reinterpret_cast<glWindowPos3dCallback>(OpenGLGetProcAddress("glWindowPos3d"));
	glWindowPos3d(x,y,z);
}
glWindowPos3dCallback glWindowPos3d = glWindowPos3dDispatcher;

void glWindowPos3dvDispatcher(const GLdouble * v){
	glWindowPos3dv = reinterpret_cast<glWindowPos3dvCallback>(OpenGLGetProcAddress("glWindowPos3dv"));
	glWindowPos3dv(v);
}
glWindowPos3dvCallback glWindowPos3dv = glWindowPos3dvDispatcher;

void glWindowPos3fDispatcher(GLfloat x,GLfloat y,GLfloat z){
	glWindowPos3f = reinterpret_cast<glWindowPos3fCallback>(OpenGLGetProcAddress("glWindowPos3f"));
	glWindowPos3f(x,y,z);
}
glWindowPos3fCallback glWindowPos3f = glWindowPos3fDispatcher;

void glWindowPos3fvDispatcher(const GLfloat * v){
	glWindowPos3fv = reinterpret_cast<glWindowPos3fvCallback>(OpenGLGetProcAddress("glWindowPos3fv"));
	glWindowPos3fv(v);
}
glWindowPos3fvCallback glWindowPos3fv = glWindowPos3fvDispatcher;

void glWindowPos3iDispatcher(GLint x,GLint y,GLint z){
	glWindowPos3i = reinterpret_cast<glWindowPos3iCallback>(OpenGLGetProcAddress("glWindowPos3i"));
	glWindowPos3i(x,y,z);
}
glWindowPos3iCallback glWindowPos3i = glWindowPos3iDispatcher;

void glWindowPos3ivDispatcher(const GLint * v){
	glWindowPos3iv = reinterpret_cast<glWindowPos3ivCallback>(OpenGLGetProcAddress("glWindowPos3iv"));
	glWindowPos3iv(v);
}
glWindowPos3ivCallback glWindowPos3iv = glWindowPos3ivDispatcher;

void glWindowPos3sDispatcher(GLshort x,GLshort y,GLshort z){
	glWindowPos3s = reinterpret_cast<glWindowPos3sCallback>(OpenGLGetProcAddress("glWindowPos3s"));
	glWindowPos3s(x,y,z);
}
glWindowPos3sCallback glWindowPos3s = glWindowPos3sDispatcher;

void glWindowPos3svDispatcher(const GLshort * v){
	glWindowPos3sv = reinterpret_cast<glWindowPos3svCallback>(OpenGLGetProcAddress("glWindowPos3sv"));
	glWindowPos3sv(v);
}
glWindowPos3svCallback glWindowPos3sv = glWindowPos3svDispatcher;

