print("index.nut at root");
print(foo() + abc());

test2("hello", 15, 242.24);

function setTimeout(callback, timeout) {
    local a;
    a = setInterval(function() {
        callback();
        clearInterval(a);
    }, timeout);
    return false;
}

// a <- setInterval(function() {
//     print("?: " + resourceLoaded("resource-default"));
//     print("?: " + resourceLoaded("resource-test"));
//     clearInterval(a);
// }, 100);


setTimeout(function() {
    print("only once");
}, 300);
