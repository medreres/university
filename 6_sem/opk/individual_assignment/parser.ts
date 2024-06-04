class InputStream {
  private pos = 0;
  private line = 1;
  private col = 0;
  private readonly input: string;

  constructor(input: string) {
    this.input = input;
  }

  next() {
    var ch = this.input.charAt(this.pos++);
    if (ch == "\n") this.line++, (this.col = 0);
    else this.col++;
    return ch;
  }

  peek() {
    return this.input.charAt(this.pos);
  }
  eof() {
    return this.peek() == "";
  }
  croak(msg) {
    throw new Error(msg + " (" + this.line + ":" + this.col + ")");
  }
}
