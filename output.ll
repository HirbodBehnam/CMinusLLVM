@number_format = private unnamed_addr constant [4 x i8] c"%d\0A\00"

declare i32 @printf(ptr noalias nocapture, ...) nounwind

define void @output(i32 signext %a) {
  call i32 (ptr, ...) @printf(ptr @number_format, i32 %a)
  ret void
}

define void @main() {
    call void (i32) @output(i32 10)
    ret void
}