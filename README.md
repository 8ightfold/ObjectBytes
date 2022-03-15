# ObjectBytes
Gets the hex data of a given object.

Basic Info
----------
For STL Containers, make sure to call the correct function.

**Keep in mind:** this will not work correctly for most class objects, you will need to implement the function yourself.

Some Containers may not work correctly with certain objects (``std::vector<bool>`` for example), and you will need to remove the reference in the for loop.

Example Output
----------
![alt text](https://github.com/8ightfold/ObjectBytes/blob/main/bytesexample.PNG?raw=true)
