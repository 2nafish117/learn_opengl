#pragma once

#include <glad/glad.h>
#include <spdlog/spdlog.h>

// #define GL_CHECK_ERROR
#define GL_ERROR_CALLBACK

// error checking, the old way
static GLenum _glCheckError(const char* file, int line)
{
	GLenum err_code;
	while ((err_code = glGetError()) != GL_NO_ERROR)
	{
		const char* error;
		switch (err_code)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		spdlog::error("[OPENGL] {} | %s ({})", file, line);
	}
	return err_code;
}

static void APIENTRY glDebugOutput(
	GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam
) {
	// ignore non-significant error/warning codes
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	spdlog::info("---------------");
	spdlog::info("Debug message ( {} ): {}", id, message);

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:				spdlog::warn("Source: API"); break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		spdlog::warn("Source: Window System"); break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	spdlog::warn("Source: Shader Compiler"); break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:		spdlog::warn("Source: Third Party"); break;
	case GL_DEBUG_SOURCE_APPLICATION:		spdlog::warn("Source: Application"); break;
	case GL_DEBUG_SOURCE_OTHER:				spdlog::warn("Source: Other"); break;
	default:								spdlog::warn("Source: Unknown"); break;
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               spdlog::warn("Type: Error"); break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: spdlog::warn("Type: Deprecated Behaviour"); break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  spdlog::warn("Type: Undefined Behaviour"); break;
	case GL_DEBUG_TYPE_PORTABILITY:         spdlog::warn("Type: Portability"); break;
	case GL_DEBUG_TYPE_PERFORMANCE:         spdlog::warn("Type: Performance"); break;
	case GL_DEBUG_TYPE_MARKER:              spdlog::warn("Type: Marker"); break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          spdlog::warn("Type: Push Group"); break;
	case GL_DEBUG_TYPE_POP_GROUP:           spdlog::warn("Type: Pop Group"); break;
	case GL_DEBUG_TYPE_OTHER:               spdlog::warn("Type: Other"); break;
	default:								spdlog::warn("Type: Unknown"); break;
	}

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         spdlog::warn("Severity: high"); break;
	case GL_DEBUG_SEVERITY_MEDIUM:       spdlog::warn("Severity: medium"); break;
	case GL_DEBUG_SEVERITY_LOW:          spdlog::warn("Severity: low"); break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: spdlog::warn("Severity: notification"); break;
	default:							 spdlog::warn("Severity: Unknown"); break;
	}
}

#ifdef GL_CHECK_ERROR
#define glCheckError() _glCheckError(__FILE__, __LINE__)
#undef GL_CHECK_ERROR
#else
#define glCheckError() /* nothing */
#endif