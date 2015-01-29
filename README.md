## ~~Sublime Text~~
# Slime Text!
###Current Version: 0.1a

#### *The text editor that isn't quite as good as Sublime Text!*

A mini project that started as a result of one of my classes,
*Slime Text* is just a fun little program that I like to add features to whenever I think of them. Nothing serious, otherwise there'd be a GUI and more than just 10 lines of text allowed! (Although that is subject to change :) )

##Usage
####Print the [current] file's contents
    ~$ p

####Write new text to a specified line (We're not going to make it easy for you)
    ~$ a <LINE NO.> <...>

####Find text in the file; Line numbers with the text are printed to console
    ~$ / <...>

####Save your changes!
    ~$ w

####Quit *SlimeText*
    ~$ q

##Upcoming Features
+ More commands
    ~$ h                //help command
    ~$ cp <LINE NO.>    //copy text
    ~$ x <LINE NO.>     //cut text
    ~$ ps <LINE NO.>    //paste text
    ~$ wq               //save and quit
+ Throw warnings when invalid commands are entered
+ Throw warnings for exceeding max character limit per line
+ Throw warnings for exceeding max no. of lines per file
+ Maybe implement ~$ i command for info on text file like:
 - File type
 - number of words, characters, etc
 - most used word
 - creation date
+ Save as command?

##Changelog
####Version 0.1a
+ First push!
+ basic commands
 - ~$ a <LINE NO.> <...> to append text to specified line
 - ~$ p to print text
 - ~$ w to save changes
 - ~$ / <...> to find text in file
 - ~$ q to quit program
+ File can have up to 10 lines of text
