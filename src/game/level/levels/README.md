# Level file format
- line 1 - map type
- line 2+ - objects (enemies, walls) with position. Format: name x y [params]
## Objects
### player
1. param `wasd`/`arrows` - keys to use to control player
 
### enemy-ballon 
Basic enemy that changes direction on collision
1. param `up`/`down`/`left`/`right` - start direction
 
### powerup-more-bombs
Powerup that gives player more bombs

### empty 
Empty tile

### wall 
Wall tile