# MFC Painting Application

C++

Visual Studio 2012

The purpose of this project is to design and implement a program that can be used for simple drawing. Painting was developed using Windows API technology. Windows API is a standard program interface between Windows systems and Windows applications. It is actually a set of standard functions provided for applications. These functions can be used to call Windows system functions, such as window management, graphics device interface, network programming, etc.

The functions implemented by this program are as follows:

1. Click "Draw", a drop-down menu appears, select one of straight line, curve, rectangle, fan shape, borderless fan shape and ellipse.

2. The event handler for this shape is responded.

3. Click "Function", a drop-down menu appears, click the color, line type and line width, the corresponding dialog box appears. After selecting, click the dialog box "OK" to complete the setting.

4. Start drawing in the blank area. The background records the coordinates of the mouse press, move, and bounce, and draws.

5. Click "Function", a drop-down menu appears, select the font, and display it in the blank area.

6. After sliding the interface down, and then open it again, the drawing in the blank area is still retained to achieve redrawing.

7. The above functions are implemented in the MFC interface
