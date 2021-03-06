'use strict';

load('jstests/concurrency/fsm_libs/runner.js');

var dir = 'jstests/concurrency/fsm_workloads';

var blacklist = [
    // Disabled due to known bugs
    'yield_sort.js', // SERVER-17011 Cursor can return objects out of order if updated during query

    // Disabled due to MongoDB restrictions and/or workload restrictions

    // These workloads take too long when composed because eval takes a
    // global lock and the composer doesn't honor iteration counts:
    'remove_single_document_eval.js',
    'update_simple_eval.js',

    // These workloads take too long when composed because server-side JS
    // is slow and the composer doesn't honor iteration counts:
    'remove_single_document_eval_nolock.js',
    'update_simple_eval_nolock.js',
].map(function(file) { return dir + '/' + file; });

// SERVER-16196 re-enable executing workloads
// runCompositionOfWorkloads(ls(dir).filter(function(file) {
//     return !Array.contains(blacklist, file);
// }));
