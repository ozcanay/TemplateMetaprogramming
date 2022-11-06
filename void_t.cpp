// https://stackoverflow.com/questions/27687389/how-does-void-t-work
// https://www.cppstories.com/2019/07/detect-overload-from-chars/#how-does-stdvoid_t-work
// https://stackoverflow.com/questions/49045422/combining-void-t-and-enable-if
// https://stackoverflow.com/questions/44858395/why-is-the-template-specialization-not-chosen/44858464#44858464 -> Just append a void() at the end to make the specialization match for the second template parameter, as the left expression is discarded and the type of void() is void, which matches the primary template's second template parameter. COMMA OPERATOR!

/*
template< class... >
using void_t = void;
*/

// std::void_t is just an **identity** type trait that is void no matter what.
// https://stackoverflow.com/questions/44858395/why-is-the-template-specialization-not-chosen?noredirect=1&lq=1, https://ideone.com/QUJxId

