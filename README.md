# **Animation Programming by FEON**

## **Summary**
- [Informations](#Informations)
- [Work](#Work)
- [Difficulties](#Difficulties)
- [References](#References)

<br>

## **Informations**

The engine used can cause data races, therefore the mesh sometimes doesn't appear or is black. Just restart the application until the mesh is displayed.  
The program runs in x86, Debug and Release.

<br>

## **Work**

Done
---
- skeleton / mesh draw in T-Pose
- skeleton / mesh draw when running / walking
- slerp between animation's frames to smooth

<br>

In progress
---
- smooth transition between walking / running animations (crossfade AKA blending)

<br>

## **Difficulties**

- we had some problems with the maths, the functions for the matrices were not all for the same format, we use matrices in line
- building the architecture of the program was quite complicated
- working during the holidays is difficult: we were not necessarily available and did not always have access to good equipment / a good connection

<br>

## **References**

- [Interpolations](https://keithmaggio.wordpress.com/2011/02/15/math-magician-lerp-slerp-and-nlerp/)
- [IK and FK simply explained](https://www.youtube.com/watch?v=0a9qIj7kwiA)

<br>

[Top of the page](#top)
