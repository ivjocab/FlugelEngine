#pragma once
#include <stdint.h>
#include <glew/include/GL/glew.h>
#include <gl/GL.h>
#include <GLM.hpp>

struct OpenGLState {
	bool lighting = false;
	bool cull_faces = true;
	bool depth_test = true;
	bool color_material = true;
	bool texture2D = true;

	uint32_t src_blend, dst_blend;
	uint32_t poly_mode = GL_FRONT_AND_BACK, poly_fill = GL_FILL;
};


struct VTX_arr {
	std::vector<glm::vec3> vertices;
	GLenum draw_mode = GL_STATIC_DRAW;
};

// Non-Interleaved Mesh - Data Blocks
struct NIMesh {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> uvs;

	std::vector<uint32_t> indices;
	std::vector<uint16_t> h_indices; // in case it has halfsized indices

	GLenum draw_mode;
	GLenum polytype;
};

struct GPUMesh {
	uint32_t vtx_id = 0;
	uint32_t norm_id = 0;
	uint32_t uvs_id = 0;
	uint32_t num_vtx = 0;

	uint32_t idx_id = 0;
	uint64_t num_idx = 0;
};