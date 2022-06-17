/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan
 */

#ifndef __PRAGMA_UTIL_BAKING_HPP__
#define __PRAGMA_UTIL_BAKING_HPP__

#include "pragma/clientdefinitions.h"
#include <vector>

namespace pragma {class CLightComponent; struct LightmapDataCache;};
namespace uimg {class ImageBuffer;};
class ModelSubMesh;
namespace util::baking
{
	DLLCLIENT util::ParallelJob<std::shared_ptr<uimg::ImageBuffer>> bake_directional_lightmap_atlas(
		const std::vector<::pragma::CLightComponent*> &lights,
		const std::vector<ModelSubMesh*> meshes,
		const std::vector<std::string> &entityUuids,
		uint32_t width,uint32_t height,
		::pragma::LightmapDataCache *optLightmapDataCache=nullptr
	);
};

#endif
