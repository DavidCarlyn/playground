var character = {
    x: 2,
    y: 102,
    sprite : 153,
    yVelocity : 1,
    isJumping : false
};

var PIXELS_PER_TILE = 8;
 
var background = getMap("map");
paper(7);

console.log(background);

exports.update = function () {
    var newY = character.y;
    var newX = character.x;
    if (btn.right) newX += 1;
    if (btn.left)  newX -= 1;
    if (btn.A && !character.isJumping) {
        character.yVelocity = -20;
        character.isJumping = true;
    }

    if (character.isJumping) {
        character.yVelocity += 1;
    }
    
    if (character.yVelocity < 0) {
        newY -= 1;
    } else {
        newY += 1;
    }
    
    if (!xCollision(newX) && !mapCollision(newX, character.y)) {
        character.x = newX;
    }
    if (!yCollision(newY) && !mapCollision(character.x, newY)) {
        character.y = newY;
    } else {
        character.isJumping = false;
        character.yVelocity = 1;
    }
 

    cls();
    draw(background, 0, 0);
    sprite(character.sprite, character.x, character.y);
};

function mapCollision(x, y) {
    var collided = false;
    background.items.forEach(row => {
        row.forEach(item => {
            if (item != null) {
                var start = item.x * PIXELS_PER_TILE
                var end = start + PIXELS_PER_TILE
                if (x + PIXELS_PER_TILE > start && x < end) {
                    start = item.y * PIXELS_PER_TILE
                    end = start + PIXELS_PER_TILE
                    if (y + PIXELS_PER_TILE > start && y < end) {
                        collided = true;
                        return;
                    }
                }
            }
        });
        if (collided) return;
    });
    return collided
}

function xCollision(x) {
    if (x < 0) return true;
    if (x > 121) return true;

    return false;
}

function yCollision(y) {
    if (y > 104) return true;
    if (y < 0) return true;

    return false;
}