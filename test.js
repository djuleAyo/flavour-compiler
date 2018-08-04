
// TEST 1 LAMBDAS CAN BE NESTED SO WE REMEMBER A LIST OR PARENTS
// var l1 = function() {
//     var x = 3;
//     y = 10;
//     var l2 = function() {
// 	    console.log(x);
// 	    x = 5;
// 	    var l3 = function() {
// 	        console.log(y);
// 	    }
// 	    return l3;
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

//==============================================================================

//TEST 2 lambda sees parenting scope

// function a() {
//     var x = 1;
//     return function() {
//         console.log(x);
//     }
// }

// function b(func) {
//     var x = 3;
//     func()
// }

// b(a())

//==============================================================================

//TEST 3 - 2 lambdas share parent scope

// function a() {
//     var x = 5

//     return {
//         f1: function () {
//             x++;
//             console.log(x);
//             return x;
//         },
//         f2: function () {
//             x /= 2;
//             console.log(x);
//         }
//     }
// }

// var x = a();
// x.f1(); x.f1(); x.f1()
// x.f2()
// x.f2()

//==============================================================================

//TEST4 EVERY LAMBDA REMEMBERS PARENT SCOPE not only returned ones

// var x;

// function init () {
//     var y = 3;
//     x = function () {
//         console.log(y);
//     }
//     function lambda2()
//     {
//         return "as";
//     }
//     return "neki drugi return";
// }

// init()

// x()

//==============================================================================

//test MAP IS NOT A SCOPE!!

// function c1 () {
//     var msg = "skope od c1"
//     return {
//         y: 3,
//         f1: function () {
//             console.log(`hello ${msg}`);
//         }
//     }
// }

// x = c1()
// x.f1()


//=============================================================================


//TEST 6 - LAMBDAS SEARCH IN PARENTING SCOPE 1ST
// var x = 3;
// (function () {
//     var x = 4;
//   })()


//=============================================================================

var l1, l2

{
    var x = 3
    l1 = function lambda1() {
        return function lambda2() {
            // var x = 7;
            console.log(x)
        }

    }

}

{
    // var x = 5;
    l2 = l1()
}

{
    // var x = 2;
    {
        l2();
    }
}
