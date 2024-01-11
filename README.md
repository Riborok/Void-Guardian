# Void Guardian
___
Engage in dynamic gameplay featuring an extensive arsenal of weapons and formidable adversaries, as you navigate 
through the void. Face the relentless Reapers, swift and deadly adversaries that must be defeated to ensure the 
void's safety. Find new weapons, navigate treacherous landscapes, and transition to the next level through portals.

## Chapters
___
### 1. [Survive and Thrive](#survive-and-thrive)
### 2. [Gameplay](#gameplay)
### 3. [Rooms](#rooms)
### 4. [Characters](#characters)
### 5. [Guns and Bullets](#guns-and-bullets)
### 6. [Controls](#controls)
### 7. [Author](#author)
### 8. [License](#license)

## Survive and Thrive
___
<img src="./readme img/game screens/Game.png" alt="Game" width="500" height="440">

Embark on a challenging survival adventure with the goal of reaching the highest level. Be ready for growing 
challenges as the amount of rooms increases and arenas expand in size at each level. Move through larger spaces, 
face more enemies, and prepare for tougher opponents. Your success depends on finding powerful weapons that are 
essential to overcome the increasing challenges in this cosmic battle.

## Gameplay
___
In the ever-evolving gameplay of Void Guardian, the transition between levels is marked by distinct thresholds that 
significantly influence the gaming experience. These thresholds act as key milestones, introducing notable changes 
to various parameters, ensuring a progressive and engaging journey for players.

### Parameter Gradation
Between each threshold, the changes in parameters are gradual, ensuring a smooth progression in difficulty and 
complexity. However, the transition from one threshold to another brings about more pronounced alterations, 
making the gameplay experience more challenging and visually distinct.

### Threshold Values
FIRST_THRESHOLD = 6

SECOND_THRESHOLD = 9

### Level Thresholds
* 0 Threshold (Before FIRST_THRESHOLD): In the initial stages of the game, before reaching the FIRST_THRESHOLD, 
players experience a gradual introduction to the game's mechanics. Challenges are relatively mild, offering a 
chance to familiarize themselves with the controls and basic gameplay;

* 1 Threshold (Before SECOND_THRESHOLD): As players surpass the FIRST_THRESHOLD but remain below the SECOND_THRESHOLD, 
the game's intensity starts to escalate. Parameters shift, creating a more demanding environment. However, these 
changes are still incremental, allowing players to adapt progressively to the evolving challenges;

* 2 Threshold (After SECOND_THRESHOLD): Beyond the SECOND_THRESHOLD, the game enters a stable phase. Here, 
parameters cease to fluctuate, offering a consistent and challenging experience. Visual elements, such as 
background and room structures, remain constant, creating a sense of stability in the game's aesthetics.

### Level-changeable parameters

1. **Gun Number (for enemy guns and armory rooms) and Enemy Character Number Generation:**
   - Utilizes an exponential distribution, where lower exponents correspond to higher probabilities of obtaining
     larger values. This affects the gun spawn number and enemy spawn number. Result: higher chances of encountering
     powerful weapons and formidable adversaries with each level, amplifying gameplay challenge.
   - Gradually decreases the exponents with level and decreases more sharply with changes in threshold.

2. **Background and Boundary Numbers:**
   - Witness specific changes at each threshold for noticeable aesthetic shifts.

3. **Enemy Spawn Configuration:**
   - Adjusts enemy quantity and spawn intervals based on the level.
   - The amount of enemies gradually increases, and the spawn interval decreases with level and more sharply with 
     a change in the threshold.

4. **Arena Random Size:**
   - Defines the minimum and maximum size of the arena.
   - Gradually increases with the level and increases more sharply with changes in the threshold.

5. **Bullet Spread:**
   - Refers to the spread of enemy shots.
   - Gradually decreases with the level and decreases more sharply with changes in the threshold.

6. **Map Dimensions:**
   - Determines the amount of rooms horizontally and vertically.
   - Gradually increases with the level and increases more sharply with changes in the threshold.

## Rooms
___
In the enigmatic universe of Void Guardian, players navigate through various rooms, each presenting unique challenges 
and opportunities for progression.

   ### Room Types:

   ### 1. Portal Room

Entrance Portal: 

<img src="./readme img/game screens/InPortal.png" alt="In Portal" width="467" height="391">

Exit Portal:

<img src="./readme img/game screens/OutPortal.png" alt="Out Portal" width="467" height="391">

Description: The portal room serves as a gateway to new levels. It features both an entrance and an exit portal. 
To enter the portal, press the take key. The entrance portal transports players to the starting menu, providing 
an opportunity to regroup and strategize. Conversely, stepping into the exit portal propels players to the next 
level, ensuring an ever-expanding cosmic adventure.

   ### 2. Arena Room

<img src="./readme img/game screens/Arena.png" alt="Arena" width="706" height="367">

Description: In the arena room, players face formidable adversaries. Victory is achieved by defeating all enemies 
within the arena. The intensity of battles increases with each level, demanding strategic prowess and combat skills.
   
   ### 3. Armory Room

<img src="./readme img/game screens/Armory.png" alt="Armory" width="469" height="459">

Description: The armory room holds the promise of powerful weaponry. Players have the chance to discover and equip 
new weapons, enhancing their combat capabilities. To take a weapon, press the take button

## Characters
___

In the cosmic battle of Void Guardian, you encounter a variety of characters, each with unique attributes and roles. 
Understanding these characteristics is essential for survival.

| Player Characters                                                                           | Health | Armor | Armor Strength | Speed |
|---------------------------------------------------------------------------------------------|--------|-------|----------------|-------|
| <img src="./readme img/characters/Character_0.png" alt="Character0" width="60" height="80"> | 100    | 30    | 1.15           | 0.6   |
| <img src="./readme img/characters/Character_1.png" alt="Character1" width="60" height="80"> | 120    | 40    | 1.3            | 0.4   |
| <img src="./readme img/characters/Character_2.png" alt="Character2" width="60" height="80"> | 90     | 20    | 1              | 0.8   |

| Enemy Characters                                                                            | Health | Armor | Armor Strength | Speed |
|---------------------------------------------------------------------------------------------|--------|-------|----------------|-------|
| <img src="./readme img/characters/Character_3.png" alt="Character3" width="60" height="80"> | 40     | 10    | 0.15           | 0.3   |
| <img src="./readme img/characters/Character_4.png" alt="Character4" width="60" height="80"> | 55     | 20    | 0.45           | 0.4   |
| <img src="./readme img/characters/Character_5.png" alt="Character5" width="60" height="80"> | 70     | 30    | 0.8            | 0.5   |

Playable characters are controlled by the player, while enemies pose a threat and must be defeated for progress 
in the game.

## Guns and Bullets
___
In the dynamic world of the game, understanding the mechanics behind damage and weaponry is crucial for survival and 
success. The damage inflicted by bullets is calculated based on a formula that considers armor strength and 
penetration. Here's a glimpse of the damage calculation formula:

```
character.armor_strength -= bullet.armor_penetration;
if (character.armor_strength < 0) { character.armor_strength = 0; }

damage = bullet.damage - character.armor_strength * character.armor;
if (damage > 0) { character.health -= damage; }
```

Available arsenal, each with its unique characteristics. The table below provides an overview of various guns, 
detailing their reload time, bullet type, damage, armor penetration, and speed. Each weapon corresponds to a 
specific type of bullet.

| Gun                                                                         | Reload Time | Bullet                                                          | Damage | Armor Penetration | Speed |
|-----------------------------------------------------------------------------|-------------|-----------------------------------------------------------------|--------|-------------------|-------|
| <img src="./readme img/guns/Gun_0.png" alt="Gun0" width="17" height="11">   | 750         | <img src="./readme img/bullets/Bullet_0.png" alt="Bullet0">     | 8      | 0.05              | 3     | 
| <img src="./readme img/guns/Gun_1.png" alt="Gun1" width="17" height="14">   | 800         | <img src="./readme img/bullets/Bullet_1.png" alt="Bullet1">     | 11     | 0.05              | 3.2   | 
| <img src="./readme img/guns/Gun_2.png" alt="Gun2" width="20" height="14">   | 600         | <img src="./readme img/bullets/Bullet_2.png" alt="Bullet2">     | 9      | 0.075             | 2.9   | 
| <img src="./readme img/guns/Gun_3.png" alt="Gun3" width="27" height="12">   | 1200        | <img src="./readme img/bullets/Bullet_3.png" alt="Bullet3">     | 19     | 0.1               | 2.7   | 
| <img src="./readme img/guns/Gun_4.png" alt="Gun4" width="15" height="14">   | 800         | <img src="./readme img/bullets/Bullet_4.png" alt="Bullet4">     | 13     | 0.075             | 3     | 
| <img src="./readme img/guns/Gun_5.png" alt="Gun5" width="21" height="15">   | 600         | <img src="./readme img/bullets/Bullet_5.png" alt="Bullet5">     | 12     | 0.05              | 3     | 
| <img src="./readme img/guns/Gun_6.png" alt="Gun6" width="30" height="17">   | 1000        | <img src="./readme img/bullets/Bullet_6.png" alt="Bullet6">     | 23     | 0.125             | 4     | 
| <img src="./readme img/guns/Gun_7.png" alt="Gun7" width="30" height="18">   | 850         | <img src="./readme img/bullets/Bullet_7.png" alt="Bullet7">     | 20     | 0.1               | 4.2   | 
| <img src="./readme img/guns/Gun_8.png" alt="Gun8" width="39" height="11">   | 350         | <img src="./readme img/bullets/Bullet_8.png" alt="Bullet8">     | 13     | 0.075             | 4.2   | 
| <img src="./readme img/guns/Gun_9.png" alt="Gun9" width="33" height="12">   | 400         | <img src="./readme img/bullets/Bullet_9.png" alt="Bullet9">     | 13     | 0.125             | 3     | 
| <img src="./readme img/guns/Gun_10.png" alt="Gun10" width="37" height="12"> | 750         | <img src="./readme img/bullets/Bullet_10.png" alt="Bullet10">   | 22     | 0.2               | 3.2   | 
| <img src="./readme img/guns/Gun_11.png" alt="Gun11" width="39" height="15"> | 600         | <img src="./readme img/bullets/Bullet_11.png" alt="Bullet11">   | 20     | 0.25              | 4     | 
| <img src="./readme img/guns/Gun_12.png" alt="Gun12" width="33" height="19"> | 250         | <img src="./readme img/bullets/Bullet_12.png" alt="Bullet12">   | 16     | 0.1               | 5     | 
| <img src="./readme img/guns/Gun_13.png" alt="Gun13" width="42" height="20"> | 550         | <img src="./readme img/bullets/Bullet_13.png" alt="Bullet13">   | 23     | 0.2               | 2.75  | 
| <img src="./readme img/guns/Gun_14.png" alt="Gun14" width="32" height="17"> | 450         | <img src="./readme img/bullets/Bullet_14.png" alt="Bullet14">   | 25     | 0.225             | 3.25  | 
| <img src="./readme img/guns/Gun_15.png" alt="Gun15" width="35" height="16"> | 1500        | <img src="./readme img/bullets/Bullet_15.png" alt="Bullet15">   | 32     | 0.3               | 4.2   |

Weapon Rarity Increases from Top to Bottom. Choose wisely to face increasingly challenging adversaries and ensure 
victory in the ever-evolving battleground.

## Controls
___
<img src="./readme img/game screens/Control.png" alt="Control" width="329" height="423">

To customize controls, simply click on the button you want to change—it will become highlighted. Then, press the 
button you wish to assign to the selected action (press Esc to cancel). Note that there are only two reserved 
buttons: Esc (to go back and call pause) and F11 (to toggle fullscreen mode).

## Author
___
* Egor Pankratiev

## License
___
This game is released under the MIT License. For more information, check the LICENSE file.