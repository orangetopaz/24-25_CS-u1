`"What to \"print?\": "; str line = ~.l
`"How many lines?: "; int loops = ~.w
`"What execution mode? [1/2]: "; int mode = ~.c
if mode = 1{
    loop.f loops{
        `line, "\n"
    }
}
if mode = 2{
    `(line, "\n")*loops
}
else {
    `.error "Invalid Mode"
}