Extract everything from [boost_1_34_1.7z](https://www.boost.org/users/history/version_1_34_1.html) here.

# Building Boost
Building Boost requires building bjam. Because the bjam build script doesn't work on modern Windows, a prebuilt binary is given for ease.

If you want to build bjam yourself though, run `build.bat` in `tools\jam\src`. Once done, find it in `bin.ntx86\` and copy it to the Boost src folder.

To build Boost:
```
bjam --toolset=msvc-8.0 --stagedir=../stage link=static stage
```