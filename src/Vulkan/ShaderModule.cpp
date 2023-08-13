/*
 * Emeraude/Vulkan/ShaderModule.cpp
 * This file is part of Emeraude
 *
 * Copyright (C) 2012-2023 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude
 * 
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "ShaderModule.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;
	using namespace Saphir;

	ShaderModule::ShaderModule (const std::shared_ptr< Device > & device, const std::shared_ptr< AbstractShader > & shader, VkShaderModuleCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(device), m_shader(shader)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.codeSize = 0;
		m_createInfo.pCode = nullptr;
	}

	ShaderModule::ShaderModule (const std::shared_ptr< Device > & device, const VkShaderModuleCreateInfo & createInfo, const std::shared_ptr< AbstractShader > & shader) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo), m_shader(shader)
	{

	}

	ShaderModule::~ShaderModule ()
	{
		this->destroyFromHardware();
	}

	bool
	ShaderModule::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this shader module !");

			return false;
		}

		if ( m_shader == nullptr )
		{
			Tracer::error(ClassId, "There is no source shader associated !");

			return false;
		}

		if ( !m_shader->isCompiled() )
		{
			Tracer::error(ClassId, "The source shader is not compiled !");

			return false;
		}

		const auto & binary = m_shader->binary();

		m_createInfo.codeSize = binary.size() * sizeof(uint32_t);
		m_createInfo.pCode = binary.data();

		const auto result = vkCreateShaderModule(this->device()->handle(), &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create a shader module : " << vkResultToCString(result) << " !";

			return false;
		}

		if ( !this->preparePipelineShaderStageCreateInfo() )
		{
			Tracer::error(ClassId, "Unable to prepare the pipeline shader stage create info !");

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The shader module " << m_handle << " (" << this->identifier() << ") is successfully created !";

		return true;
	}

	bool
	ShaderModule::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the shader module " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyShaderModule(this->device()->handle(), m_handle, nullptr);

			TraceSuccess{ClassId} << "The shader module " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkShaderModule
	ShaderModule::handle () const noexcept
	{
		return m_handle;
	}

	VkShaderModuleCreateInfo
	ShaderModule::createInfo () const noexcept
	{
		return m_createInfo;
	}

	const VkPipelineShaderStageCreateInfo &
	ShaderModule::pipelineShaderStageCreateInfo () const noexcept
	{
		return m_pipelineShaderStageCreateInfo;
	}

	bool
	ShaderModule::preparePipelineShaderStageCreateInfo () noexcept
	{
		/*VkSpecializationMapEntry mapEntry{};
		mapEntry.constantID = 0;
		mapEntry.offset = 0;
		mapEntry.size = 0;*/

		m_specializationInfo.mapEntryCount = m_mapEntries.size();
		m_specializationInfo.pMapEntries = m_mapEntries.data();
		m_specializationInfo.dataSize = 0;
		m_specializationInfo.pData = nullptr;

		m_pipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		m_pipelineShaderStageCreateInfo.pNext = nullptr;
		/*
		VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT = 0x00000001,
		VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT = 0x00000002,
		*/
		m_pipelineShaderStageCreateInfo.flags = 0;
		switch ( m_shader->type() )
		{
			case ShaderType::VertexShader :
				m_pipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
				break;

			case ShaderType::TesselationControlShader :
				m_pipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
				break;

			case ShaderType::TesselationEvaluationShader :
				m_pipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
				break;

			case ShaderType::GeometryShader :
				m_pipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
				break;

			case ShaderType::FragmentShader :
				m_pipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
				break;

			case ShaderType::ComputeShader :
				m_pipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
				break;
		}
		m_pipelineShaderStageCreateInfo.module = m_handle;
		m_pipelineShaderStageCreateInfo.pName = "main";
		m_pipelineShaderStageCreateInfo.pSpecializationInfo = m_mapEntries.empty() ? nullptr : &m_specializationInfo;

		return true;
	}

	std::shared_ptr< Saphir::AbstractShader >
	ShaderModule::shader () const noexcept
	{
		return m_shader;
	}
}
