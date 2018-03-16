# BVH Viewer

A simple `.bvh` file player with UI that allows interpolation between two animations. 

![BVH Viewer](https://i.imgur.com/ydiU462.png)
![Interpolation](https://i.imgur.com/ZMnwPNk.png)

## Build

### Dependencies
* Qt 5.9.2
* QtCreator 4.4.1
* [NGL](https://github.com/NCCA/NGL);

### Install

```
qmake BVHViewer.pro
make clean
make
./BVHViewer
```

### How to

1. Choose where to load the first `.bvh` file from drop down menu (either in `Animation 1` or `Animation 2`)
1. Load a first `.bvh` file in `Animation 1` (by default) 
1. Use the player's button to interact with the animation (play/pause/next frame/previous frame/backward/forward/reset animation)
1. Load a second `.bvh` file in `Animation 2`
1. Use the player's button to interact with the animation (play/pause/next frame/previous frame/backward/forward/reset animation)
1. Click on `Interpolate` to perform blending between the two chosen animations: a new dialog window will open where different options can be set for interpolation
1. See the blended result by choosing `Blended Animation` from the drop down menu

### Documentation

Doxygen documentation in `/doc` folder.

## Resources
* Icons: [NounProject](https://thenounproject.com);
* `.bvh` files: [CMU Graphics Lab Motion Capture Database](http://mocap.cs.cmu.edu/resources.php), converted files from [Bruce Hahn](https://sites.google.com/a/cgspeed.com/cgspeed/motion-capture/daz-friendly-release)