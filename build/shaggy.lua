shaggy = {
    GraphicsComponent = {
        filename = "shaggy.png"
    },
    NPCComponent = {
        phrase = "I'M A SCARY shag!!!"
    },
    CollisionComponent = {
        boundingBox = {0, 0, 32, 32},
        collide = function(this, second)
            shaggy.CollisionComponent.test()
        end
    }
}