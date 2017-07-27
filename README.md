# TSMI
Triploit Stack Machine

Fibonacci:

```ruby
[
    1 i set
    1 t1 set
    0 t2 set
    0 next set

    [ dup $i <= ] [
        $t1 $t2 +
        next set

        $t2 t1 set
        $next t2 set

        $next out " " out
        1 $i + i set
    ] while
] fib func

14 fib!
```

