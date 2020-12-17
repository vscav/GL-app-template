#pragma once
#ifndef _GLTF_HPP_
#define _GLTF_HPP_

#include <engine/dependencies/glm.hpp>
#include <engine/dependencies/tiny_gltf.h>

glm::mat4 getLocalToWorldMatrix(
    const tinygltf::Node &node, const glm::mat4 &parentMatrix);

void computeSceneBounds(
    const tinygltf::Model &model, glm::vec3 &bboxMin, glm::vec3 &bboxMax);

#endif /* _GLTF_HPP_ */