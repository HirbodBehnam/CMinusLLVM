@number_print_format = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@number_scan_format = private unnamed_addr constant [3 x i8] c"%d\00"

declare i32 @printf(ptr noalias nocapture, ...) nounwind
declare i32 @scanf(ptr noalias nocapture, ...) nounwind

define void @output(i32 signext %a) {
  call i32 (ptr, ...) @printf(ptr @number_print_format, i32 %a)
  ret void
}

define i32 @input() {
  %a.ptr = alloca i32, align 4
  call i32 (ptr, ...) @scanf(ptr @number_scan_format, ptr %a.ptr)
  %a = load i32, ptr %a.ptr, align 4 
  ret i32 %a
}

define void @main() {
  %a = call i32 () @input()
  call void (i32) @output(i32 %a)
  ret void
}