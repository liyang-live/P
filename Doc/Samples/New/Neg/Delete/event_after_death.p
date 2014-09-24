event Shot;

main machine Gun {
    var target:machine;

    start state init {
        entry {
            target = new Target();
            send target, Shot;
            send target, Shot;
        }
    }
}

machine Target {
    start state init {
        on Shot goto die;
    }

    state die {
        entry { raise(halt); }
    }
}