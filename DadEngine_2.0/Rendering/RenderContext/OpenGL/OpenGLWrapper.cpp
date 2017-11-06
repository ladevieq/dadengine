#include "OpenGLWrapper.hpp"


namespace DadEngine::Rendering::OpenGLWrapper
{
	HMODULE hModule = LoadLibraryA("opengl32.dll");


	/*
		Wrapper functions implementation

		Function pointer variable
	*/
	PFNGLGETSTRINGIPROC PFNgetStringi = nullptr;


	// Buffer stuff
	PFNGLGENBUFFERSPROC PFNglGenBuffers = nullptr;

	PFNGLBINDBUFFERPROC PFNglBindBuffer = nullptr;

	PFNGLBUFFERDATAPROC PFNglBufferData = nullptr;

	PFNGLDRAWBUFFERSPROC PFNglDrawBuffers = nullptr;

	PFNGLDELETEBUFFERSPROC PFNglDeleteBuffers = nullptr;


	// Vertex buffer stuff
	PFNGLGENVERTEXARRAYSPROC PFNglGenVertexArrays = nullptr;

	PFNGLBINDVERTEXARRAYPROC PFNglBindVertexArray = nullptr;

	PFNGLVERTEXATTRIBPOINTERPROC PFNglVertexAttribPointer = nullptr;

	PFNGLENABLEVERTEXATTRIBARRAYPROC PFNglEnableVertexAttribArray = nullptr;

	PFNGLDISABLEVERTEXATTRIBARRAYPROC PFNglDisableVertexAttribArray = nullptr;

	PFNGLDELETEVERTEXARRAYSPROC PFNglDeleteVertexArrays = nullptr;


	// Shader stuff
	PFNGLCREATESHADERPROC PFNglCreateShader = nullptr;

	PFNGLSHADERSOURCEPROC PFNglShaderSource = nullptr;

	PFNGLCOMPILESHADERPROC PFNglCompileShader = nullptr;

	PFNGLATTACHSHADERPROC PFNglAttachShader = nullptr;

	PFNGLGETSHADERIVPROC PFNglGetShaderiv = nullptr;

	PFNGLGETSHADERINFOLOGPROC PFNglGetShaderInfoLog = nullptr;

	PFNGLDETACHSHADERPROC PFNglDetachShader = nullptr;

	PFNGLDELETESHADERPROC PFNglDeleteShader = nullptr;


	// Shader program stuff
	PFNGLCREATEPROGRAMPROC PFNglCreateProgram = nullptr;

	PFNGLLINKPROGRAMPROC PFNglLinkProgram = nullptr;

	PFNGLUSEPROGRAMPROC PFNglUseProgram = nullptr;

	PFNGLBINDATTRIBLOCATIONPROC PFNglBindAttribLocation = nullptr;

	PFNGLBINDFRAGDATALOCATIONPROC PFNglBindFragDataLocation = nullptr;

	PFNGLGETPROGRAMIVPROC PFNglGetProgramiv = nullptr;

	PFNGLGETPROGRAMINFOLOGPROC PFNglGetProgramInfoLog = nullptr;

	PFNGLDELETEPROGRAMPROC PFNglDeleteProgram = nullptr;


	// Framebuffer stuff
	PFNGLBINDFRAMEBUFFERPROC PFNglBindFramebuffer = nullptr;



	const GLubyte* __stdcall getStringi(GLenum _InName, GLuint _InIndex)
	{
		return PFNgetStringi(_InName, _InIndex);
	}


	// Buffer stuff
	void __stdcall glGenBuffers(GLsizei _InBufferCount, GLuint* _InBuffers)
	{
		PFNglGenBuffers(_InBufferCount, _InBuffers);
	}

	void __stdcall glBindBuffer(GLenum _InTarget, GLuint _InBuffer)
	{
		PFNglBindBuffer(_InTarget, _InBuffer);
	}

	void __stdcall glBufferData(GLenum _InTarget, GLsizeiptr _InSize, const void* _InData, GLenum _InUsage)
	{
		PFNglBufferData(_InTarget, _InSize, _InData, _InUsage);
	}

	void __stdcall glDrawBuffers(GLsizei _InCount, GLenum* _inBuffers)
	{
		PFNglDrawBuffers(_InCount, _inBuffers);
	}

	void __stdcall glDeleteBuffers(GLsizei _InBufferCount, GLuint* _InBuffers)
	{
		PFNglDeleteBuffers(_InBufferCount, _InBuffers);
	}


	// Vertex buffer stuff
	void __stdcall glGenVertexArrays(GLsizei _InArrayCount, GLuint* _InArrays)
	{
		PFNglGenVertexArrays(_InArrayCount, _InArrays);
	}

	void __stdcall glBindVertexArray(GLuint _InArrayIndex)
	{
		PFNglBindVertexArray(_InArrayIndex);
	}

	void __stdcall glVertexAttribPointer(GLuint _InIndex, GLint _InSize, GLenum _InType, GLboolean _InNormalized, GLsizei _InStride, const void* _InPointer)
	{
		PFNglVertexAttribPointer(_InIndex, _InSize, _InType, _InNormalized, _InStride, _InPointer);
	}

	void __stdcall glEnableVertexAttribArray(GLuint _InIndex)
	{
		PFNglEnableVertexAttribArray(_InIndex);
	}

	void __stdcall glDisableVertexAttribArray(GLuint _InIndex)
	{
		PFNglDisableVertexAttribArray(_InIndex);
	}

	void __stdcall glDeleteVertexArrays(GLsizei _InArrayCount, GLuint* _InArrays)
	{
		PFNglDeleteVertexArrays(_InArrayCount, _InArrays);
	}


	// Shader stuff
	GLuint  __stdcall glCreateShader(GLenum _InShaderType)
	{
		return PFNglCreateShader(_InShaderType);
	}

	void  __stdcall glShaderSource(GLuint _InShaderID, GLsizei _InCount, const GLchar* const *_InShaderSource, GLint* _InLength)
	{
		PFNglShaderSource(_InShaderID, _InCount, _InShaderSource, _InLength);
	}

	void __stdcall glCompileShader(GLuint _InShaderID)
	{
		PFNglCompileShader(_InShaderID);
	}

	void __stdcall glAttachShader(GLuint _InProgramID, GLuint _InShaderID)
	{
		PFNglAttachShader(_InProgramID, _InShaderID);
	}

	void __stdcall glDetachShader(GLuint _InProgramID, GLuint _InShaderID)
	{
		PFNglDetachShader(_InProgramID, _InShaderID);
	}

	void __stdcall glGetShaderiv(GLuint _InShaderID, GLenum _InType, GLint* _OutParams)
	{
		PFNglGetShaderiv(_InShaderID, _InType, _OutParams);
	}

	void __stdcall glGetShaderInfoLog(GLuint _InShaderID, GLsizei _InBufferSize, GLsizei *_InLength, GLchar *_InInfoLog)
	{
		PFNglGetShaderInfoLog(_InShaderID, _InBufferSize, _InLength, _InInfoLog);
	}

	void __stdcall glDeleteShader(GLuint _InShaderID)
	{
		PFNglDeleteShader(_InShaderID);
	}


	// Shader program stuff
	GLuint __stdcall glCreateProgram()
	{
		return PFNglCreateProgram();
	}

	void __stdcall glLinkProgram(GLuint _InProgramID)
	{
		PFNglLinkProgram(_InProgramID);
	}

	void __stdcall glUseProgram(GLuint _InProgramID)
	{
		PFNglUseProgram(_InProgramID);
	}

	void __stdcall glBindAttribLocation(GLuint _InProgramID, GLuint _InBindIndex, const char* _InBindName)
	{
		PFNglBindAttribLocation(_InProgramID, _InBindIndex, _InBindName);
	}

	void __stdcall glBindFragDataLocation(GLuint _InProgramID, GLuint _InBindIndex, const char* _InBindName)
	{
		PFNglBindFragDataLocation(_InProgramID, _InBindIndex, _InBindName);
	}

	void __stdcall glGetProgramiv(GLuint _InProgramID, GLenum _InType, GLint* _OutParams)
	{
		PFNglGetProgramiv(_InProgramID, _InType, _OutParams);
	}

	void __stdcall glGetProgramInfoLog(GLuint _InProgramID, GLsizei _InBufferSize, GLsizei *_InLength, GLchar *_InInfoLog)
	{
		PFNglGetProgramInfoLog(_InProgramID, _InBufferSize, _InLength, _InInfoLog);
	}

	void __stdcall glDeleteProgram(GLuint _InProgramID)
	{
		PFNglDeleteProgram(_InProgramID);
	}


	// Framebuffer stuff
	void __stdcall glBindFrameBuffer(GLenum _InType, GLuint _InFramebuffer)
	{
		PFNglBindFramebuffer(_InType, _InFramebuffer);
	}


#if defined(GL_EXT_vertex_array)
	PFNGLDRAWARRAYSEXTPROC PFNglDrawArrays = nullptr;

	void __stdcall glDrawArrays(GLenum _InMode, GLint _InFirst, GLsizei _InCount)
	{
		PFNglDrawArrays(_InMode, _InFirst, _InCount);
	}
#endif

#if defined(WINDOWS)

	PFNWGLCREATECONTEXTATTRIBSARBPROC PFNwglCreateContextAttribsARB = nullptr;

	HGLRC _stdcall wglCreateContextAttribsARB(HDC _InHDC, HGLRC _InSharedHGLRC, const int* _InAttribList)
	{
		return PFNwglCreateContextAttribsARB(_InHDC, _InSharedHGLRC, _InAttribList);
	}

	#if defined(WGL_EXT_swap_control)
	PFNWGLSWAPINTERVALEXTPROC PFNwglSwapIntervalEXT = nullptr;

	BOOL __stdcall wglSwapIntervalEXT(int _InInterval)
	{
		return PFNwglSwapIntervalEXT(_InInterval);
	}
	#endif
#endif


	/*
		Functions loading function
	*/
	void* glLoadFunction(const char* _InFuncName)
	{
		void* func = (void*)wglGetProcAddress(_InFuncName);

		if (func == 0)
		{
			func = (void *)GetProcAddress(hModule, _InFuncName);
		}

		return func;
	}


	/*
		Load common OpenGL functions
	*/
	void glLoadStandardFunctions()
	{
		PFNgetStringi = (PFNGLGETSTRINGIPROC)glLoadFunction("glGetStringi");


		// Buffer stuff
		PFNglGenBuffers = (PFNGLGENBUFFERSPROC)glLoadFunction("glGenBuffers");

		PFNglBindBuffer = (PFNGLBINDBUFFERPROC)glLoadFunction("glBindBuffer");

		PFNglBufferData = (PFNGLBUFFERDATAPROC)glLoadFunction("glBufferData");

		PFNglDrawBuffers = (PFNGLDRAWBUFFERSPROC)glLoadFunction("glDrawBuffers");

		PFNglDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glLoadFunction("glDeleteBuffers");


		// Vertex buffer stuff
		PFNglGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glLoadFunction("glGenVertexArrays");

		PFNglBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glLoadFunction("glBindVertexArray");

		PFNglVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glLoadFunction("glVertexAttribPointer");

		PFNglEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glLoadFunction("glEnableVertexAttribArray");

		PFNglDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glLoadFunction("glDisableVertexAttribArray");

		PFNglDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glLoadFunction("glDeleteVertexArrays");


		// Shader stuff
		PFNglCreateShader = (PFNGLCREATESHADERPROC)glLoadFunction("glCreateShader");

		PFNglShaderSource = (PFNGLSHADERSOURCEPROC)glLoadFunction("glShaderSource");

		PFNglCompileShader = (PFNGLCOMPILESHADERPROC)glLoadFunction("glCompileShader");

		PFNglAttachShader = (PFNGLATTACHSHADERPROC)glLoadFunction("glAttachShader");

		PFNglDetachShader = (PFNGLDETACHSHADERPROC)glLoadFunction("glDetachShader");

		PFNglGetShaderiv = (PFNGLGETSHADERIVPROC)glLoadFunction("glGetShaderiv");

		PFNglGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glLoadFunction("glGetShaderInfoLog");

		PFNglDeleteShader = (PFNGLDELETESHADERPROC)glLoadFunction("glDeleteShader");


		// Shader program stuff
		PFNglCreateProgram = (PFNGLCREATEPROGRAMPROC)glLoadFunction("glCreateProgram");

		PFNglLinkProgram = (PFNGLLINKPROGRAMPROC)glLoadFunction("glLinkProgram");

		PFNglUseProgram = (PFNGLUSEPROGRAMPROC)glLoadFunction("glUseProgram");

		PFNglBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glLoadFunction("glBindAttribLocation");

		PFNglBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)glLoadFunction("glBindFragDataLocation");

		PFNglGetProgramiv = (PFNGLGETPROGRAMIVPROC)glLoadFunction("glGetProgramiv");

		PFNglGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glLoadFunction("glGetProgramInfoLog");

		PFNglDeleteProgram = (PFNGLDELETEPROGRAMPROC)glLoadFunction("glDeleteProgram");


		// Framebuffer stuff
		PFNglBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glLoadFunction("glBindFramebuffer");
	}

	/*
		Load functions from OpenGL extensions
	*/
	void glLoadExtensionsFunctions()
	{
#if defined(GL_EXT_vertex_array)
		PFNglDrawArrays = (PFNGLDRAWARRAYSEXTPROC)glLoadFunction("glDrawArrays");
#endif
#if defined(WINDOWS) 
		PFNwglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)glLoadFunction("wglCreateContextAttribsARB");
	#if defined(WGL_EXT_swap_control)
		PFNwglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)glLoadFunction("wglSwapIntervalEXT");
	#endif
#endif
	}

	
	void glInit()
	{
		int32 iNumExtensions = 0;
		int32 iMajor = 0, iMinor = 0;

		glGetIntegerv(GL_MAJOR_VERSION, &iMajor);
		glGetIntegerv(GL_MINOR_VERSION, &iMinor);

		printf("%s%d%s%d\n", "Version : ", iMajor, ".", iMinor);
		glGetIntegerv(GL_NUM_EXTENSIONS, &iNumExtensions);
		printf("%s%d\n", "Extension count : ", iNumExtensions);

		glLoadStandardFunctions();
		glLoadExtensionsFunctions();

		for (int32 i = 0; i < iNumExtensions; i++)
		{
			printf("%s\n", getStringi(GL_EXTENSIONS, i));
		}
	}
}