# Engine TODO-list

## GENERAL CHECKS
- Check the for-loop-range like "for ( const auto & item : items | std::views::values )" performances.

## GENERAL BUGS
- Check for light coherence, create a built-in scene with a fixed directional light and multiple materials.
- Unloading objets from the scene do not release vulkan memory.
- Issue on Linux with X11, multi-monitors and NVIDIA proprietary driver. More info : https://forums.developer.nvidia.com/t/external-monitor-freezes-when-using-dedicated-gpu/265406

## CONSOLE
- Bring back a useful console behavior.

## LIBRARIES
- Add RLE to the Targa image format.
- OBJ adds the write process.
- Remove old MDx 3D format.
- Finish the native format.

## RESOURCES
- Merge Font from PixelFactory and FontResource.
- Check for JSON resource the direct data description.
- Check for JSON resource the store resource addition.

## SCENE :
- Create a shared dynamic uniform buffer for static entities instead using push_constants as they normally won't move between frame. Thus, it will only hold the model matrix.
- Re-enable particles emitters. This must fundamentally be reworked from the ground.
- Check enable/disable audio on scene switching. (Shared with AUDIO section)

## MATERIAL :
- Create a shared dynamic uniform buffer when a material do not use sampler. Pay attention to the real benefit of that solution.
- Create a material editor in javascript (application side).

## TEXTURING :
- Read settings when generate samplers.
- Finish 1D and 3D textures.

## RENDERING :
- Enable additional render targets next to the main one in order to create shadow maps, 2D textures and reflections.
- Study and create the cubemap rendering (single-pass) in order to be able to produce reflections and shadow cubemap.
- Improve the rendering branches to reduce cost.
- Check sprite blending.
- Check sprite texture clamping to edges.
- Re-enable screenshot from engine.

## SHADERS GENERATION :
- Check source and binary caches.
- Prepare a way to use manual sources.
- Re-enable normal calculation bypass when the surface is not facing a light.

## LIGHTING :
- Fix the ambient light update against render target which use it.
- Re-enable the ambient light color generated by the averaging active lights color.
- Check the ambient light color generated by a texture.
- Check what is the light matrix for shadow map and how to update it. Hint, this is MVP matrix from the light point of view.
- Check light radius against entities to discard some useless rendering.
- Shadow maps : Create a re-usable shadow map for ephemere lights.

## PHYSICS :
- Enable the rotational physics.

## ANIMATION :
- (Prior) Check all animatable properties for all objects.
- Remove Variant for std::any.

## OVERLAY :
- Rework the composable overlay to create native menu.
- Check the TextWriter class.

## AUDIO :
- Check to stop sound from an inactive scene. (Shared with SCENE section)

## GENERAL VULKAN :
- Check validation layers and debug messenger relationship. (According to khronos, this is valid to create the debug messenger without validation layers)
- Fix texture loading. (UINT->UNORM) Convert data before ? or not ?
- Use of separated image from sampler in GLSL when useful.
- Find a better solutions to handle shared uniform buffer objects.
- Find a better way to create and store descriptor set layout.
- Find a way to order the rendering by pipeline layout to reduce the binding cost per draw.
- Check for the right way to push constant from the right shader declaration to right stage in vulkan. (GraphicsShaderGenerator.cpp:254)
- Check waitIdle() for device in every corner of the engine. Sometimes the device is lost.
- Analyse UBO and instanced VBO usage and make a better and global shared UBO/VBO optimization for short life entity.
