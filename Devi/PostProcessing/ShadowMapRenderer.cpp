#include "ShadowMapRenderer.h"
#include "Math/glm/gtc/matrix_transform.hpp"

namespace Devi
{
	//ShadowMapRenderer::ShadowMapRenderer(int shadowMapWidth, int shadowMapHeight)
	//{
	//	m_depthTexture.CreateEmptyTexture2D(GL_DEPTH_COMPONENT, shadowMapHeight, shadowMapWidth, GL_DEPTH_COMPONENT, GL_FLOAT);
	//	m_depthTexture.AddTextureParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	m_depthTexture.AddTextureParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//	m_depthTexture.AddTextureParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	m_depthTexture.AddTextureParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	
	//	m_framebuffer.AttachTexture2DToFrameBuffer(GL_DEPTH_ATTACHMENT, m_depthTexture, 0);
	//
	//	//learnopengl : framebuffers are not compelete without color buffers, we need to explcitly tell opengl we dont need it.
	//	glDrawBuffer(GL_NONE);
	//	glReadBuffer(GL_NONE);
	//
	//	//m_lightOrthoMatrix = glm::ortho(-500.0, 500.0, -100.0, 100.0);
	//	//m_lightViewMatrix = glm::lookAt(glm::vec3(0, 100, 0), , glm::vec3(0.0, -1.0, 0.0));
	//	//NOTE we should probably use the camera position for the ortho projection.
	//}
	//
	//void ShadowMapRenderer::RenderDepthMap()
	//{
	//	m_framebuffer.Bind();
	//
	//}
}

