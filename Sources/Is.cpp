bool IsDigit(char Char){
    return (Char > 0x2F && Char < 0x3A);
}
bool IsLetter(char Char){
    return (Char > 0x40 && Char < 0x5B)||(Char > 0x60 && Char < 0x7B);
}
bool IsWhiteSpace(char Char){
    return (Char==0x20||Char==0x9);
}
