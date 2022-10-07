//
// create n^k from predecessors.
//
// Note:  m(1) = 0 // no multiplication required
//        m(2) = 1 // only 1 way
//        m(3) = 2 // can only get to three thru 2
//        m(4) = 2 // n^2, then n^2 * n^2
//        m(5) = 3 // n^2, then n^3, then n^2 * n^3
//        m(6) = 3 // n^2 n^3 then n^3 * n^3
//        m(7) = 4
//
//     NOTE:  m(a*b) = m(a) + m(b)
//     Proof:
//        
