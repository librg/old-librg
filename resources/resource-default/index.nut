::print("index.nut at root");
::print(foo() + abc());

native.test2("hello", 15, 242.24);

// a <- setInterval(function() {
//     print("?: " + resourceLoaded("resource-default"));
//     print("?: " + resourceLoaded("resource-test"));
//     clearInterval(a);
// }, 100);


function setTimeout(callback, timeout) {
    local a;
    a = native.setInterval(function() {
        native.clearInterval(a);
        callback();
    }, timeout);
    return false;
}

setTimeout(function() {
    ::print("only once");
}, 300);

/**
 * Function that logs to server console
 * provided any number of provided values
 * NOTE: addes prefix [debug] in front of output
 *
 * @param  {...}  any number of arguments
 * @return none
 */
function dbg(...) {
    ::print("[debug] " + JSONEncoder.encode(vargv));
}

// quadtree test

/*class XY {
    x = 0;
    y = 0;

    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

local playerpos = [XY(0,0), XY(0,1), XY(10,1), XY(10,13), XY(1,2), XY(0,1),XY(0,0), XY(0,1), XY(10,1), XY(10,13), XY(1,2), XY(0,1),XY(0,0), XY(0,1), XY(10,1), XY(10,13), XY(1,2), XY(0,1),XY(0,0), XY(0,1), XY(10,1), XY(10,13), XY(1,2), XY(0,1),XY(0,0), XY(0,1), XY(10,1), XY(10,13), XY(1,2), XY(0,1)];
local range = 5;

class AABB {
    center = null;
    halfdim = 0;

    constructor(center, halfdim) {
        this.center = center;
        this.halfdim = halfdim;
    }

    function contains(point) {
        if( center.x - halfdim <= point.x && center.x + halfdim >= point.x &&
            center.y - halfdim <= point.y && center.y + halfdim >= point.y ) {
                return true;
            } else {
                return false;
            }
    }
}

class QTree {
    QT_MAX_NODES = 4;
    boundary = null;
    nodes = null;
    trees = null;
    isroot = false;
    pushed = 0;

    constructor(aabb, isroot = true) {
        this.boundary = aabb;
        this.nodes = [];
        this.trees = [];
        this.isroot = isroot;
    }

    function insert(point) {
        if(!boundary.contains(point)) {
            return false;
        }

        if(pushed <= QT_MAX_NODES) {
            nodes.push(point);
            pushed++;
            return true;
        }

        if(trees.len() == 0) {
            subdivide();
        }

        foreach (t in trees) {
            if(t.insert(point)) {
                return true;
            }
        }

        return false;
    }

    function createChild(boundary) {
        local t = QTree(boundary, false);

        // NOTE(ZaKlaus): This isn't needed in case of stream querying!
        foreach (n in nodes) {
            if(t.boundary.contains(n)) {
                t.nodes.push(n);
            }
        }
        trees.push(t);
    }

    function subdivide() {
        local hd = boundary.halfdim / 2.0;

        local nwc = XY(boundary.center.x - hd, boundary.center.y - hd);
        local nwb = AABB(nwc, hd);
        local nec = XY(boundary.center.x + hd, boundary.center.y - hd);
        local neb = AABB(nec, hd);
        local swc = XY(boundary.center.x - hd, boundary.center.y + hd);
        local swb = AABB(swc, hd);
        local sec = XY(boundary.center.x + hd, boundary.center.y + hd);
        local seb = AABB(sec, hd);

        createChild(nwb);
        createChild(neb);
        createChild(swb);
        createChild(seb);
    }

    function dump(level = 0) {
        local indent = "";
        for (local i = 0; i<level; ++i) {
            indent += "  ";
        }
        print(indent + "Tree with nodes: " + (nodes.len()));
        foreach (tree in trees) {
            tree.dump(level + 1);
        }
    }
}

local root = QTree(AABB(XY(0,0), 50));

foreach (p in playerpos) {
    root.insert(p);
}

print("Total nodes: " + playerpos.len());
root.dump();*/

native.eventAddHandler("onDeveloperDrinksVodka", function (amount, name) {
    ::print("*Gulp* " + amount + " " + name);
});

//native.eventServerTrigger("onDeveloperDrinksVodka", [12, "Vlad"]);
native.eventServerTrigger("onVodkaTooWeak", ["plenty"]);
native.eventServerTrigger("onTestMessageRequested", []);

// NOTE(zaklaus): This should not work, since it is SQ->SQ call.
// This gets solved by using internal event system on the SQ side.
native.eventServerTrigger("onDeveloperDrinksVodka", []);
