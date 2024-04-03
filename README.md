# 2D array generation  
- Settings (dimension, occurences, distinct characters)
- Randomize based on setting to make a 2D array 

# Path finding  
- Algorithm for pathfinding (recommend A*) with high cost on turning points 
- Determine if path turn over 3 times, kill that path. 
- Help (path recommendation) feature
- Visualized with Godot [here](https://github.com/khuongduy354/astar-godot/tree/master)
![astargodot](https://github.com/khuongduy354/astar-godot/assets/42113313/b733d684-81f2-44bf-af3c-c1bc18b66bbd)

# Save games
- Create configs struct for save (player infos, records, stages)
- Save as binary file 


# Core game flow  
- Keyboard command -> checking -> delete cells
- Game Finish checker  
- Continuous stages (not increasing difficulty) 
- Time tracking 

# Others
- Keyboard input  
- Colors & Visual effects (use lib)

# Tasks: 
Me: Pathfinding, Help Feature, glueing game flows: checkwin, new stages, board logics,...

Quynh: Keyboard input, visual, save game, 2D array generation

 

# Todo:  
- make sure game continue, with increase difficulties (sizes) as config  
- cout: press f to suggest, and color when suggest. 
- menu print pretty: title + name input