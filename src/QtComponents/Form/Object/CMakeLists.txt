target_sources(BartaSceneCreator PUBLIC
    TransformationForm.cpp
    SpriteForm.cpp
    HitboxForm.cpp
    RotationForm.cpp
    VelocityForm.cpp
    MassCenterForm.cpp
)

add_subdirectory(Hitbox)

add_subdirectory(Sprite)
