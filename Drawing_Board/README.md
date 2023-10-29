# Drawing Board Based on Hand Recognization Based by OpenCV

In this project, I was primarily responsible for building the overall framework and implementing gesture recognition.Because I have almost no knowledge of AI and computer vision, I just searched for relevant information and found some projects that I can use.

When using specific hand gesture, the program would record the track of moving hand. After that, it could tell what the shape was.In the end, I designed the whole system just operated by hand recogniztion, which meant you can just change hand gesture to control it.

**Below are the relevant files:**
|folder_name/file_name|content&function|
|------|------|
|_code_|**codes of this project**|
|_project_presentation.pdf_|**final project PPT**|
|_project_report.pdf_|**final project report**|


**Face Recognition and Hand Detection**

.xml files: Different from Databases such as Access, Oracle and SQL Server, DATABASESprovide more powerful data storage and analysis capabilities, such as: data indexing, sorting, lookup,correlation consistency, etc., EXTENSIBLE Markup language only stores data. In fact, one of thebiggest differences between it and other data representations is that EXTENSIBLE Markup Languageis extremely simple, a seemingly trivial advantage that sets it apart.

The simplicity of XML makes it easy to read/write data in any application, which makes XMLquickly become a data exchange language (such languages mainly include XML, JSON, etc.,commonly used in interface calls, configuration files, data storage, etc.), although different applicationsalso support other data exchange formats. But soon they will all support XML, which means programscan more easily combine information generated on Windows, Mac OS, Linux, and other platforms, and then easily load XML data into programs, analyze it, and output results in XML format.

**Use Global Variable to Change Mode**

Global variables are a programming term derived from the division of variables. Variables aredivided into local and global variables, local variables can also be called internal variables. Variablesncreated by an object or function are usually local variables and can only be referenced internally, not by other objects or functions.

In this project, the reason we chose the global variables is that Using global variables takes up more memory (because of their long lifetime), but in today's world of highly configured computers, this should not be a problem unless you are using global variables for large objects, which should be avoided whenever possible. Programs that use global variables run faster (because memory doesn't need to be reallocated), and not much faster either. Namespace pollution of local variables can be avoided without using too many variables. When a global variable has the same name as a local variable, the local variable is used and the global variable is shielded.

So in the every while loop, the first thing is to check and judge the global variables’ value, the whole system will jump to the different function modes, and realize the relative functions we want.

The effect was like:

<div align=center>
<img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/2f5ad440-3e23-4fd2-8a80-40ae977f0c51"  />
  <img src="https://github.com/anOrangeCat1/projects_sustech/assets/99580008/eb3a5576-5a0b-46bb-b0b7-a51330639eda"  />
</div>

**video link:**

youtube: https://www.youtube.com/watch?v=hBGSzM4NXlc

bilibili: https://www.bilibili.com/video/BV1Ay4y1N7nA
