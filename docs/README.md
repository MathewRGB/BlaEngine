# Doc Folder Usage

The only purpose of this folder is storing files for the API and project documentation<br/>
We use Doxygen for documenting our API.

## Doxygen Usage

Doxygen right now points on the project folder /include and the source folder.<br/>
All markdown files under those folders become part of the documentaion as well.<br/>
For ensuring consistency we use "///" as doc-strings. For more details look at:<br/>
https://www.stack.nl/~dimitri/doxygen/manual/index.html <br/>
Or take a look into the /include folder for getting examples how our Doxygen-doc-style looks like. <br/>

The generated Doxygen-page and everthing generated from Doxygen shouldn't be part of our repository yet. <br/>
It is proposed to use a Doxygen-plugin for your Toolchain or IDE for automatically generate the doc-strings and <br/>
for making your life easier.

## Doxygen Documentation Generation

First of all, install Doxygen on your computer. <br/>
Then:

    $ cd docs/
    $ doxygen Doxyfile.in

... and the documentation will be created into your docs folder.
