
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/hash.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Mvc\Router\Annotations
 *
 * A router that reads routes annotations from classes/resources
 *
 *<code>
 * $di['router'] = function() {
 *
 *		//Use the annotations router
 *		$router = new \Phalcon\Mvc\Router\Annotations(false);
 *
 *		//This will do the same as above but only if the handled uri starts with /robots
 * 		$router->addResource('Robots', '/robots');
 *
 * 		return $router;
 *	};
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Router_Annotations) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc\\Router, Annotations, phalcon, mvc_router_annotations, phalcon_mvc_router_ce, phalcon_mvc_router_annotations_method_entry, 0);

	zend_declare_property_null(phalcon_mvc_router_annotations_ce, SL("_handlers"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(phalcon_mvc_router_annotations_ce, SL("_processed"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_mvc_router_annotations_ce, SL("_controllerSuffix"), "Controller", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_mvc_router_annotations_ce, SL("_actionSuffix"), "Action", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_router_annotations_ce, SL("_routePrefix"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Adds a resource to the annotations handler
 * A resource is a class that contains routing annotations
 *
 * @param string handler
 * @param string prefix
 * @return Phalcon\Mvc\Router\Annotations
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, addResource) {

	zval *_0;
	zval *handler_param = NULL, *prefix_param = NULL;
	zval *handler = NULL, *prefix = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &handler_param, &prefix_param);

	if (Z_TYPE_P(handler_param) != IS_STRING && Z_TYPE_P(handler_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'handler' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(handler_param) == IS_STRING) {
		handler = handler_param;
	} else {
		ZEPHIR_INIT_VAR(handler);
		ZVAL_EMPTY_STRING(handler);
	}
	if (!prefix_param) {
		ZEPHIR_INIT_VAR(prefix);
		ZVAL_EMPTY_STRING(prefix);
	} else {
	if (Z_TYPE_P(prefix_param) != IS_STRING && Z_TYPE_P(prefix_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'prefix' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(prefix_param) == IS_STRING) {
		prefix = prefix_param;
	} else {
		ZEPHIR_INIT_VAR(prefix);
		ZVAL_EMPTY_STRING(prefix);
	}
	}


	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 3);
	zephir_array_fast_append(_0, prefix);
	zephir_array_fast_append(_0, handler);
	zephir_update_property_array_append(this_ptr, SL("_handlers"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_processed"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Adds a resource to the annotations handler
 * A resource is a class that contains routing annotations
 * The class is located in a module
 *
 * @param string module
 * @param string handler
 * @param string prefix
 * @return Phalcon\Mvc\Router\Annotations
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, addModuleResource) {

	zval *_0;
	zval *module_param = NULL, *handler_param = NULL, *prefix_param = NULL;
	zval *module = NULL, *handler = NULL, *prefix = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &module_param, &handler_param, &prefix_param);

	if (Z_TYPE_P(module_param) != IS_STRING && Z_TYPE_P(module_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'module' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(module_param) == IS_STRING) {
		module = module_param;
	} else {
		ZEPHIR_INIT_VAR(module);
		ZVAL_EMPTY_STRING(module);
	}
	if (Z_TYPE_P(handler_param) != IS_STRING && Z_TYPE_P(handler_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'handler' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(handler_param) == IS_STRING) {
		handler = handler_param;
	} else {
		ZEPHIR_INIT_VAR(handler);
		ZVAL_EMPTY_STRING(handler);
	}
	if (!prefix_param) {
		ZEPHIR_INIT_VAR(prefix);
		ZVAL_EMPTY_STRING(prefix);
	} else {
	if (Z_TYPE_P(prefix_param) != IS_STRING && Z_TYPE_P(prefix_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'prefix' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(prefix_param) == IS_STRING) {
		prefix = prefix_param;
	} else {
		ZEPHIR_INIT_VAR(prefix);
		ZVAL_EMPTY_STRING(prefix);
	}
	}


	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 5);
	zephir_array_fast_append(_0, prefix);
	zephir_array_fast_append(_0, handler);
	zephir_array_fast_append(_0, module);
	zephir_update_property_array_append(this_ptr, SL("_handlers"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_processed"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Produce the routing parameters from the rewrite information
 *
 * @param string uri
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, handle) {

	zephir_fcall_cache_entry *_8 = NULL, *_16 = NULL;
	HashTable *_2, *_6, *_10, *_14;
	HashPosition _1, _5, _9, _13;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *uri_param = NULL, *realUri = NULL, *annotationsService = NULL, *handlers, *controllerSuffix, *scope = NULL, *prefix = NULL, *dependencyInjector = NULL, *handler = NULL, *controllerName = NULL, *lowerControllerName = NULL, *namespaceName = NULL, *moduleName = NULL, *sufixed = NULL, *handlerAnnotations = NULL, *classAnnotations = NULL, *annotations = NULL, *annotation = NULL, *methodAnnotations = NULL, *lowercased = NULL, *method = NULL, *collection = NULL, *_0, **_3, *_4 = NULL, **_7, **_11, *_12 = NULL, **_15;
	zval *uri = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &uri_param);

	if (!uri_param) {
		ZEPHIR_INIT_VAR(uri);
		ZVAL_EMPTY_STRING(uri);
	} else {
	if (Z_TYPE_P(uri_param) != IS_STRING && Z_TYPE_P(uri_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'uri' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(uri_param) == IS_STRING) {
		uri = uri_param;
	} else {
		ZEPHIR_INIT_VAR(uri);
		ZVAL_EMPTY_STRING(uri);
	}
	}


	if (!(uri && Z_STRLEN_P(uri))) {
		ZEPHIR_CALL_METHOD(&realUri, this_ptr, "getrewriteuri",  NULL);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(realUri, uri);
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_processed"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		ZEPHIR_INIT_VAR(annotationsService);
		ZVAL_NULL(annotationsService);
		ZEPHIR_OBS_VAR(handlers);
		zephir_read_property_this(&handlers, this_ptr, SL("_handlers"), PH_NOISY_CC);
		if (Z_TYPE_P(handlers) == IS_ARRAY) {
			ZEPHIR_OBS_VAR(controllerSuffix);
			zephir_read_property_this(&controllerSuffix, this_ptr, SL("_controllerSuffix"), PH_NOISY_CC);
			zephir_is_iterable(handlers, &_2, &_1, 0, 0);
			for (
			  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
			  ; zephir_hash_move_forward_ex(_2, &_1)
			) {
				ZEPHIR_GET_HVALUE(scope, _3);
				if (Z_TYPE_P(scope) == IS_ARRAY) {
					ZEPHIR_OBS_NVAR(prefix);
					zephir_array_fetch_long(&prefix, scope, 0, PH_NOISY TSRMLS_CC);
					if (Z_TYPE_P(prefix) == IS_STRING) {
						if (zephir_start_with(realUri, prefix, 0)) {
							continue;
						}
					}
					if (Z_TYPE_P(annotationsService) == IS_OBJECT) {
						_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dependencyInjector"), PH_NOISY_CC);
						ZEPHIR_CPY_WRT(dependencyInjector, _0);
						if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
							ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_router_exception_ce, "A dependency injection container is required to access the 'annotations' service");
							return;
						}
						ZEPHIR_INIT_NVAR(_4);
						ZVAL_STRING(_4, "annotations", 0);
						ZEPHIR_CALL_METHOD(&annotationsService, dependencyInjector, "getshared", NULL, _4);
						zephir_check_temp_parameter(_4);
						zephir_check_call_status();
					}
					ZEPHIR_OBS_NVAR(handler);
					zephir_array_fetch_long(&handler, scope, 1, PH_NOISY TSRMLS_CC);
					ZEPHIR_INIT_NVAR(lowerControllerName);
					ZEPHIR_INIT_NVAR(namespaceName);
					if (zephir_memnstr_str(handler, SL("\\"), "phalcon/mvc/router/annotations.zep", 148)) {
						ZEPHIR_INIT_NVAR(controllerName);
						zephir_get_class_ns(controllerName, handler, 0 TSRMLS_CC);
						zephir_uncamelize(lowerControllerName, controllerName);
						zephir_get_ns_class(namespaceName, handler, 0 TSRMLS_CC);
					} else {
						ZEPHIR_CPY_WRT(controllerName, handler);
						zephir_uncamelize(lowerControllerName, controllerName);
						ZVAL_NULL(namespaceName);
					}
					zephir_update_property_this(this_ptr, SL("_routePrefix"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
					ZEPHIR_OBS_NVAR(moduleName);
					if (!(zephir_array_isset_long_fetch(&moduleName, scope, 2, 0 TSRMLS_CC))) {
						ZEPHIR_INIT_NVAR(moduleName);
						ZVAL_NULL(moduleName);
					}
					ZEPHIR_INIT_NVAR(sufixed);
					ZEPHIR_CONCAT_VV(sufixed, handler, controllerSuffix);
					ZEPHIR_CALL_METHOD(&handlerAnnotations, annotationsService, "get", NULL, sufixed);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&classAnnotations, handlerAnnotations, "getclassannotations",  NULL);
					zephir_check_call_status();
					if (Z_TYPE_P(classAnnotations) == IS_OBJECT) {
						ZEPHIR_CALL_METHOD(&annotations, classAnnotations, "getannotations",  NULL);
						zephir_check_call_status();
						if (Z_TYPE_P(annotations) == IS_ARRAY) {
							zephir_is_iterable(annotations, &_6, &_5, 0, 0);
							for (
							  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
							  ; zephir_hash_move_forward_ex(_6, &_5)
							) {
								ZEPHIR_GET_HVALUE(annotation, _7);
								ZEPHIR_CALL_METHOD(NULL, this_ptr, "processcontrollerannotation", &_8, controllerName, annotation);
								zephir_check_call_status();
							}
						}
					}
					ZEPHIR_CALL_METHOD(&methodAnnotations, handlerAnnotations, "getmethodsannotations",  NULL);
					zephir_check_call_status();
					if (Z_TYPE_P(methodAnnotations) == IS_ARRAY) {
						ZEPHIR_INIT_NVAR(lowercased);
						zephir_uncamelize(lowercased, handler);
						zephir_is_iterable(methodAnnotations, &_10, &_9, 0, 0);
						for (
						  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
						  ; zephir_hash_move_forward_ex(_10, &_9)
						) {
							ZEPHIR_GET_HMKEY(method, _10, _9);
							ZEPHIR_GET_HVALUE(collection, _11);
							if (Z_TYPE_P(collection) == IS_OBJECT) {
								ZEPHIR_CALL_METHOD(&_12, collection, "getannotations",  NULL);
								zephir_check_call_status();
								zephir_is_iterable(_12, &_14, &_13, 0, 0);
								for (
								  ; zephir_hash_get_current_data_ex(_14, (void**) &_15, &_13) == SUCCESS
								  ; zephir_hash_move_forward_ex(_14, &_13)
								) {
									ZEPHIR_GET_HVALUE(annotation, _15);
									ZEPHIR_CALL_METHOD(NULL, this_ptr, "processactionannotation", &_16, moduleName, namespaceName, lowerControllerName, method, annotation);
									zephir_check_call_status();
								}
							}
						}
					}
				}
			}
		}
		zephir_update_property_this(this_ptr, SL("_processed"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	ZEPHIR_CALL_PARENT(NULL, phalcon_mvc_router_annotations_ce, this_ptr, "handle", NULL, realUri);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Checks for annotations in the controller docblock
 *
 * @param string handler
 * @param Phalcon\Annotations\Annotation
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, processControllerAnnotation) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *handler_param = NULL, *annotation, *_0 = NULL, *_1 = NULL, *_2;
	zval *handler = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &handler_param, &annotation);

	if (Z_TYPE_P(handler_param) != IS_STRING && Z_TYPE_P(handler_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'handler' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(handler_param) == IS_STRING) {
		handler = handler_param;
	} else {
		ZEPHIR_INIT_VAR(handler);
		ZVAL_EMPTY_STRING(handler);
	}


	if (!(zephir_instance_of_ev(annotation, phalcon_annotations_annotation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'annotation' must be an instance of 'Phalcon\\Annotations\\Annotation'");
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, annotation, "getname",  NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(_0, "RoutePrefix")) {
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 0);
		ZEPHIR_CALL_METHOD(&_1, annotation, "getargument", NULL, _2);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("_routePrefix"), _1 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Checks for annotations in the public methods of the controller
 *
 * @param string module
 * @param string namespaceName
 * @param string controller
 * @param string action
 * @param Phalcon\Annotations\Annotation annotation
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, processActionAnnotation) {

	zephir_fcall_cache_entry *_7 = NULL;
	HashTable *_5, *_9;
	HashPosition _4, _8;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool isRoute;
	zval *module_param = NULL, *namespaceName_param = NULL, *controller_param = NULL, *action_param = NULL, *annotation, *name = NULL, *actionName, *routePrefix, *paths = NULL, *value = NULL, *uri = NULL, *route = NULL, *methods = NULL, *converts = NULL, *param = NULL, *convert = NULL, *conversorParam = NULL, *routeName = NULL, *_0, *_1, _2, *_3 = NULL, **_6, **_10;
	zval *module = NULL, *namespaceName = NULL, *controller = NULL, *action = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 5, 0, &module_param, &namespaceName_param, &controller_param, &action_param, &annotation);

	if (Z_TYPE_P(module_param) != IS_STRING && Z_TYPE_P(module_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'module' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(module_param) == IS_STRING) {
		module = module_param;
	} else {
		ZEPHIR_INIT_VAR(module);
		ZVAL_EMPTY_STRING(module);
	}
	if (Z_TYPE_P(namespaceName_param) != IS_STRING && Z_TYPE_P(namespaceName_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'namespaceName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(namespaceName_param) == IS_STRING) {
		namespaceName = namespaceName_param;
	} else {
		ZEPHIR_INIT_VAR(namespaceName);
		ZVAL_EMPTY_STRING(namespaceName);
	}
	if (Z_TYPE_P(controller_param) != IS_STRING && Z_TYPE_P(controller_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controller' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(controller_param) == IS_STRING) {
		controller = controller_param;
	} else {
		ZEPHIR_INIT_VAR(controller);
		ZVAL_EMPTY_STRING(controller);
	}
	if (Z_TYPE_P(action_param) != IS_STRING && Z_TYPE_P(action_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'action' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(action_param) == IS_STRING) {
		action = action_param;
	} else {
		ZEPHIR_INIT_VAR(action);
		ZVAL_EMPTY_STRING(action);
	}


	if (!(zephir_instance_of_ev(annotation, phalcon_annotations_annotation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'annotation' must be an instance of 'Phalcon\\Annotations\\Annotation'");
		return;
	}
	isRoute = 0;
	ZEPHIR_INIT_VAR(methods);
	ZVAL_NULL(methods);
	ZEPHIR_CALL_METHOD(&name, annotation, "getname",  NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING(name, "Route")) {
		isRoute = 1;
	} else {
		if (ZEPHIR_IS_STRING(name, "Get")) {
			isRoute = 1;
			ZEPHIR_INIT_BNVAR(methods);
			ZVAL_STRING(methods, "GET", 1);
		} else {
			if (ZEPHIR_IS_STRING(name, "Post")) {
				isRoute = 1;
				ZEPHIR_INIT_BNVAR(methods);
				ZVAL_STRING(methods, "POST", 1);
			} else {
				if (ZEPHIR_IS_STRING(name, "Put")) {
					isRoute = 1;
					ZEPHIR_INIT_BNVAR(methods);
					ZVAL_STRING(methods, "PUT", 1);
				} else {
					if (ZEPHIR_IS_STRING(name, "Options")) {
						isRoute = 1;
						ZEPHIR_INIT_BNVAR(methods);
						ZVAL_STRING(methods, "OPTIONS", 1);
					}
				}
			}
		}
	}
	if (isRoute == 1) {
		ZEPHIR_INIT_VAR(actionName);
		ZEPHIR_INIT_VAR(_0);
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_actionSuffix"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_STRING(&_2, "", 0);
		zephir_fast_str_replace(_0, _1, &_2, action);
		zephir_fast_strtolower(actionName, _0);
		ZEPHIR_OBS_VAR(routePrefix);
		zephir_read_property_this(&routePrefix, this_ptr, SL("_routePrefix"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_STRING(_3, "paths", 0);
		ZEPHIR_CALL_METHOD(&paths, annotation, "getnamedargument", NULL, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		if (Z_TYPE_P(paths) != IS_ARRAY) {
			ZEPHIR_INIT_VAR(paths);
			array_init(paths);
		}
		if (!(ZEPHIR_IS_EMPTY(module))) {
			zephir_array_update_string(&paths, SL("module"), &module, PH_COPY | PH_SEPARATE);
		}
		if (!(ZEPHIR_IS_EMPTY(namespaceName))) {
			zephir_array_update_string(&paths, SL("namespace"), &namespaceName, PH_COPY | PH_SEPARATE);
		}
		zephir_array_update_string(&paths, SL("controller"), &controller, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&paths, SL("action"), &actionName, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 0);
		ZEPHIR_CALL_METHOD(&value, annotation, "getargument", NULL, _3);
		zephir_check_call_status();
		if (Z_TYPE_P(value) != IS_NULL) {
			if (!ZEPHIR_IS_STRING(value, "/")) {
				ZEPHIR_INIT_VAR(uri);
				ZEPHIR_CONCAT_VV(uri, routePrefix, value);
			} else {
				ZEPHIR_CPY_WRT(uri, routePrefix);
			}
		} else {
			ZEPHIR_INIT_NVAR(uri);
			ZEPHIR_CONCAT_VV(uri, routePrefix, actionName);
		}
		ZEPHIR_CALL_METHOD(&route, this_ptr, "add", NULL, uri, paths);
		zephir_check_call_status();
		if (Z_TYPE_P(methods) != IS_NULL) {
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_STRING(_3, "methods", 0);
			ZEPHIR_CALL_METHOD(&methods, annotation, "getnamedargument", NULL, _3);
			zephir_check_temp_parameter(_3);
			zephir_check_call_status();
			if (Z_TYPE_P(methods) == IS_ARRAY) {
				ZEPHIR_CALL_METHOD(NULL, route, "via", NULL, methods);
				zephir_check_call_status();
			} else {
				if (Z_TYPE_P(methods) == IS_STRING) {
					ZEPHIR_CALL_METHOD(NULL, route, "via", NULL, methods);
					zephir_check_call_status();
				}
			}
		} else {
			ZEPHIR_CALL_METHOD(NULL, route, "via", NULL, methods);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "converts", 0);
		ZEPHIR_CALL_METHOD(&converts, annotation, "getnamedargument", NULL, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		if (Z_TYPE_P(converts) == IS_ARRAY) {
			zephir_is_iterable(converts, &_5, &_4, 0, 0);
			for (
			  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
			  ; zephir_hash_move_forward_ex(_5, &_4)
			) {
				ZEPHIR_GET_HMKEY(param, _5, _4);
				ZEPHIR_GET_HVALUE(convert, _6);
				ZEPHIR_CALL_METHOD(NULL, route, "convert", &_7, param, convert);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "conversors", 0);
		ZEPHIR_CALL_METHOD(&converts, annotation, "getnamedargument", NULL, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		if (Z_TYPE_P(converts) == IS_ARRAY) {
			zephir_is_iterable(converts, &_9, &_8, 0, 0);
			for (
			  ; zephir_hash_get_current_data_ex(_9, (void**) &_10, &_8) == SUCCESS
			  ; zephir_hash_move_forward_ex(_9, &_8)
			) {
				ZEPHIR_GET_HMKEY(conversorParam, _9, _8);
				ZEPHIR_GET_HVALUE(convert, _10);
				ZEPHIR_CALL_METHOD(NULL, route, "convert", &_7, conversorParam, convert);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "name", 0);
		ZEPHIR_CALL_METHOD(&routeName, annotation, "getnamedargument", NULL, _3);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		if (Z_TYPE_P(routeName) == IS_STRING) {
			ZEPHIR_CALL_METHOD(NULL, route, "setname", NULL, routeName);
			zephir_check_call_status();
		}
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Changes the controller class suffix
 *
 * @param string controllerSuffix
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, setControllerSuffix) {

	zval *controllerSuffix_param = NULL;
	zval *controllerSuffix = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &controllerSuffix_param);

	if (Z_TYPE_P(controllerSuffix_param) != IS_STRING && Z_TYPE_P(controllerSuffix_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerSuffix' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(controllerSuffix_param) == IS_STRING) {
		controllerSuffix = controllerSuffix_param;
	} else {
		ZEPHIR_INIT_VAR(controllerSuffix);
		ZVAL_EMPTY_STRING(controllerSuffix);
	}


	zephir_update_property_this(this_ptr, SL("_controllerSuffix"), controllerSuffix TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Changes the action method suffix
 *
 * @param string actionSuffix
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, setActionSuffix) {

	zval *actionSuffix_param = NULL;
	zval *actionSuffix = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &actionSuffix_param);

	if (Z_TYPE_P(actionSuffix_param) != IS_STRING && Z_TYPE_P(actionSuffix_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionSuffix' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(actionSuffix_param) == IS_STRING) {
		actionSuffix = actionSuffix_param;
	} else {
		ZEPHIR_INIT_VAR(actionSuffix);
		ZVAL_EMPTY_STRING(actionSuffix);
	}


	zephir_update_property_this(this_ptr, SL("_actionSuffix"), actionSuffix TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the registered resources
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Router_Annotations, getResources) {


	RETURN_MEMBER(this_ptr, "_handlers");

}
