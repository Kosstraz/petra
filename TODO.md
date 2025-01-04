**Venus :**

- Possibilité de capter les différents écrans branchés, et de switch entre eux si demandé.

**VVenus :**

- Dans '__FindGPUs()' le premier PhysicalDevice est pris, cependant une logique de capture du GPU paraît obligatoire
- Dans '__CreateLogicalDevice()' se renseigner sur la queue du device (familyQueue, ...) [vkGetPhysicalDeviceQueueFamilyProperties(...)]
- Dans 'ShowPhysicalDeviceProperties()' afficher les .limits du device physique
- Dans '__CreateLogicalDevice()' choisir le device physique en fonction d'un score jugé selon ces limites, ces "features" et et si c'est un GPU ou non.
