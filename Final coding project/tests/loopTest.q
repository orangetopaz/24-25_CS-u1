loop 5 {
    `"Hello World!\n"
}

int i
loop 5 @ i{
    `i
}

i = 0
loop ¿i = 5?{
    i++
    `"while", i
}