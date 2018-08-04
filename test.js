// var l1 = function() {
//     var x = 3;
//     y = 10;
//     var l2 = function() {
// 	console.log(x);
// 	x = 5;
// 	var l3 = function() {
// 	    console.log(y);
// 	}
// 	return l3;
//     }

//     y = 12;

//     return l2;
// }

// var y = 11;
// {
//     var a = l1()()();
// }

// t1 = l1()
// t2 = t1()

// var test = function (x) {
//     var a = 7;
//     x();
// }



//TEST 2

function a() {
    var x = 1;
    return function() {
        console.log(x);
    }
}

function b(func) {
    var x = 3;
    func()
}

b(a())
