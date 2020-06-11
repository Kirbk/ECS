ghost = {
    GraphicsComponent = {
        filename = "ghost.png"
    },
    NPCComponent = {
        phrase = "I'M A SCARY BITCH!!!"
    },
    CollisionComponent = {
        boundingBox = {0, 0, 32, 32},
        collide = function(this, second)
            ghost.CollisionComponent.test()
        end
    }
}