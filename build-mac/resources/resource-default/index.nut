// print("index.nut at root");
// print(foo() + abc());

// // test2("hello", 15, 242.24);

// function setTimeout(callback, timeout) {
//     local pointer;
//     pointer = setInterval(function() { clearInterval(pointer); callback(); }, timeout);
//     return pointer;
// }

// function timer(callback, timeout) {
//     local pointer = setInterval(callback, timeout);
//     return { Kill = function() { return clearInterval(pointer); } };
// }

// // a <- setInterval(function() {
// //     print("?: " + resourceLoaded("resource-default"));
// //     print("?: " + resourceLoaded("resource-test"));
// //     clearInterval(a);
// // }, 100);

// // local reschecker = setInterval(function() {
// //     print("is resource loaded: " + resourceLoaded("default"));
// // }, 5000);

// setTimeout(function() {
//     print("only once");
// }, 300);

// // clearInterval(reschecker);


native.test(native.resourceLoaded("resource-default"));
native.setInterval(function() {
    native.test(native.resourceLoaded("resource-default"));
}, 1000);
