package java8.effective.annotation;

import java.lang.reflect.*;

public class Annotation {
  public static void main(String[] args) throws Exception {
    int tests = 0;
    int passed = 0;
    Class<?> testClass = Class.forName("java8.effective.annotation.TestSample");
    for (Method m : testClass.getDeclaredMethods()) {
      if (m.isAnnotationPresent(Test.class)) {
        ++tests;
        try {
          m.invoke(null);
          ++passed;
        } catch (InvocationTargetException wrappedExc) {
          Throwable exc = wrappedExc.getCause();
          System.out.println(m + " failed: " + exc);
        } catch (Exception exc) {
          System.out.println("INVALID @Test: " + m);
        }
      }
    }
    System.out.printf("Passed: %d, Failed: %d%n", passed, tests - passed);
  }
}

/*
public static void java8.effective.annotation.TestSample.m3() failed: java.lang.RuntimeException: Hoge
INVALID @Test: public void java8.effective.annotation.TestSample.m5()
public static void java8.effective.annotation.TestSample.m7() failed: java.lang.RuntimeException: Foo
Passed: 1, Failed: 3

Process finished with exit code 0
*/