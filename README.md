# UnifiedGFX


UnifiedGFX library that allows you to develop your projects independently of the hardware.

There are many types of MCU and screens, and many good libraries to manage it. But I don't want my projects to depend on certain hardware, because probably I want to move to another one.

This portability have with a (little) perfomance cost. If are looking for maximum performance, this library is probably not for you. Personally, I don't mind having 30.48fps or 29.83fps, versus the advantage of not relying on hardware.

## How to use
UnifiedGFX offers abstract classes such as `IBitmap<Tcolor>`, `IReadableBitmap<Tcolor>`, `IGraphic<Tcolor>`.

On the other hand, the class `Graphic<Tcolor>` implements most of `IGraphic<Tcolor>` functions, using only `IBitmap<Tcolor>` functions `Height()`, `Width()`, and `drawPixel()`.

This way your project would have, for example, the draw function.
```c++
void draw(UGFX::IGraphic<uint16_t>& screen, uint16_t background, uint16_t color)
{
    //
}
```

## Adapting to your hardware
By design, UnifiedGFX library doesn't know about hardware or drivers. To use it with a specific hardware you could do two things:
- Use adapter pattern
- Modify your graphics libraries to implement `IGraphic<Tcolor>`

And example of how to implement `Graphic<Tcolor>` in your classes is provided in the example 'Generic'.

Also, adapters and examples are provided for AdagruitGFX, eTFT and LGVX libraries.


## Performance
The functions of the adapters are decorated with the alwaws_inline attribute, so performance should be similar to using them directly. It will be even beter if you modify your graphics libraries to implement the abstract classes of UGFX.

Actual performance will depend on how well your adapter leverages hardware features. The essential functions for UnifiedGFX to work are `IBitmap<Tcolor>` functions `Height()`, `Width()`, and `drawPixel()`. But performance will be the worse posible. 
  
If your adapter are able to override more `Graphic<Tcolor>` functions and map it to the display driver, performance improves substantially.
