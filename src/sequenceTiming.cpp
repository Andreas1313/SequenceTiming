//Because of the use of "template<typename ..." .cpp can not work. 
//For explanation see:https://www.reddit.com/r/learnprogramming/comments/vpgey4/whats_the_proper_way_to_compile_c_template/?rdt=47441
//Extraction: Template implementations need to be written in the header file, not a separate source file...
//To have similar .cpp feeling:
//At the end of "sequenceTiming.h" it is written #include "sequenceTiming.tpp" and at every function use "template<typename ...>"