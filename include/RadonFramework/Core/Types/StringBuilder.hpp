/** This class can be used to build strings without generating 
  * garbage because this class use an own memory allocator to build all Strings.
  **/
class StringBuilder
{
public:
	// Add an string or other type
	operator <<();
	// Add an string
	operator +();
	// Can be used to add a formatted string to the string.
	void AddFormat(const char* frm, ...);
	// Return an instance of the internally build string.
	String GetInstance();
protected:
	LinearAllocator allocator;
};