Virtua Partner
==============

Progmatic Windows keyboard inputs to make sparring partner in Virtua Fighter.

## System Requirements

* Windows 10
* Visual Studio 2019 (for compiling and running)
* Virtua Fighter 5 Final Tuned running in a window

## Features

- Trigger keyboard inputs progmatically to act as a sparring partner in Virtua Fighter 5 Final Tuned

- Detects when you block a move with guaranteed punishment and gives feedback on if you punish or not

- Keep statistics about how often you successfully punish with guaranteed counter

## Configuration Syntax

Virtua Partner uses text files in domain specific language to represent CPU movements.

The following hashtags can be used:

```
#recoverslow
#↑ used when a move recovers low and uses different punish from moves that recover standing

#hitslow
#↑ used when a standing move hits low and character can punish with from crouching move
```


## Limitations

**CPU Commands**

Only a few characters and situations are configured right now.

**CPU Inputs**

CPU inputs must be mapped as follows keyboard keys (this is hardcoded for now)
* Up: W
* Left: A
* Down: S
* Right: D
* Guard: G
* Punch: P
* Kick: K

**Guaranteed Punishment Feedback**

This is a work in progress and basically it only gives feedback as if you were playing as El Blaze.  Though the feedback for punch counterable moves should be accurate for other characters where PK is guarenteed at +12 or +13.

To detect if guaranteed punish or not, VF5 must be running in a Window about 1280x730 size.  Virtua Partner checks hardcoded pixel positions to determine and may not work well with a different sized Window.
